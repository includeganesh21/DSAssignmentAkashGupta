#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

const char* vertexShaderSource = R"(
    #version 330 core
    layout(location = 0) in vec3 aPosition;
    layout(location = 1) in vec3 aColor;
    uniform mat4 uModelMatrix;
    uniform mat4 uViewMatrix;
    uniform mat4 uProjectionMatrix;
    out vec3 vColor;
    void main() {
        gl_Position = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(aPosition, 1.0);
        vColor = aColor;
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    in vec3 vColor;
    uniform float uTime;
    uniform int uIsSun;
    out vec4 FragColor;
    void main() {
        vec3 color = vColor;
        if (uIsSun == 1) {
            float glow = 0.8 + 0.2 * sin(uTime * 2.0); // Pulsing effect for Sun
            color = vec3(1.0, glow, 0.3); // Orange-yellow glow
        }
        FragColor = vec4(color, 1.0);
    }
)";

// Sphere geometry
struct Sphere {
    std::vector<float> vertices;
    std::vector<float> colors;
    std::vector<unsigned int> indices;
    GLuint vao, vbo, colorBuffer, ebo;
    int indexCount;

    Sphere(float radius, int segments, glm::vec3 color) {
        for (int i = 0; i <= segments; i++) {
            float phi = (i / (float)segments) * glm::pi<float>();
            for (int j = 0; j <= segments; j++) {
                float theta = (j / (float)segments) * 2 * glm::pi<float>();
                float x = radius * sin(phi) * cos(theta);
                float y = radius * sin(phi) * sin(theta);
                float z = radius * cos(phi);
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);
                colors.push_back(color.r);
                colors.push_back(color.g);
                colors.push_back(color.b);
            }
        }
        for (int i = 0; i < segments; i++) {
            for (int j = 0; j < segments; j++) {
                int p1 = i * (segments + 1) + j;
                int p2 = p1 + 1;
                int p3 = p1 + segments + 1;
                int p4 = p3 + 1;
                indices.push_back(p1);
                indices.push_back(p2);
                indices.push_back(p3);
                indices.push_back(p2);
                indices.push_back(p4);
                indices.push_back(p3);
            }
        }
        indexCount = indices.size();

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &colorBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), colors.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
    }
};

// Shader compilation
GLuint compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "Shader compilation error: " << infoLog << std::endl;
    }
    return shader;
}

GLuint createProgram() {
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "Program linking error: " << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}

// Camera control variables
float cameraAngle = 0.0f;
float cameraDistance = 5.0f;
bool mouseDown = false;
double lastX = 0, lastY = 0;

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            mouseDown = true;
            glfwGetCursorPos(window, &lastX, &lastY);
        } else if (action == GLFW_RELEASE) {
            mouseDown = false;
        }
    }
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    if (mouseDown) {
        double dx = xpos - lastX;
        cameraAngle += dx * 0.005f;
        lastX = xpos;
        lastY = ypos;
    }
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    cameraDistance += yoffset * 0.1f;
    cameraDistance = glm::clamp(cameraDistance, 2.0f, 10.0f);
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Mini Solar System", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Setup shaders and objects
    GLuint program = createProgram();
    glUseProgram(program);

    Sphere sun(1.0f, 20, glm::vec3(1.0f, 0.5f, 0.0f)); // Sun: orange
    Sphere planet1(0.3f, 20, glm::vec3(0.0f, 0.5f, 1.0f)); // Planet1: blue
    Sphere planet2(0.4f, 20, glm::vec3(1.0f, 0.0f, 0.0f)); // Planet2: red
    Sphere moon(0.1f, 20, glm::vec3(0.7f, 0.7f, 0.7f)); // Moon: gray

    // Uniform locations
    GLint uModelMatrix = glGetUniformLocation(program, "uModelMatrix");
    GLint uViewMatrix = glGetUniformLocation(program, "uViewMatrix");
    GLint uProjectionMatrix = glGetUniformLocation(program, "uProjectionMatrix");
    GLint uTime = glGetUniformLocation(program, "uTime");
    GLint uIsSun = glGetUniformLocation(program, "uIsSun");

    // Setup viewport and matrices
    glEnable(GL_DEPTH_TEST);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetScrollCallback(window, scrollCallback);

    float time = 0.0f;
    while (!glfwWindowShouldClose(window)) {
        // Clear screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Projection and view matrices
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)width / height, 0.1f, 100.0f);
        glm::mat4 view = glm::translate(glm::rotate(glm::mat4(1.0f), cameraAngle, glm::vec3(0, 1, 0)), glm::vec3(0, 0, -cameraDistance));
        glUniformMatrix4fv(uProjectionMatrix, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uViewMatrix, 1, GL_FALSE, glm::value_ptr(view));
        glUniform1f(uTime, time);

        // Sun
        glUniform1i(uIsSun, 1);
        glm::mat4 model = glm::mat4(1.0f);
        glUniformMatrix4fv(uModelMatrix, 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(sun.vao);
        glDrawElements(GL_TRIANGLES, sun.indexCount, GL_UNSIGNED_INT, 0);

        // Planet 1 (faster, closer orbit)
        glUniform1i(uIsSun, 0);
        model = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f * sin(time), 0.0f, 2.0f * cos(time)));
        model = glm::rotate(model, time * 2.0f, glm::vec3(0, 1, 0));
        glUniformMatrix4fv(uModelMatrix, 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(planet1.vao);
        glDrawElements(GL_TRIANGLES, planet1.indexCount, GL_UNSIGNED_INT, 0);

        // Planet 2 (slower, farther orbit)
        model = glm::translate(glm::mat4(1.0f), glm::vec3(4.0f * sin(time * 0.5f), 0.0f, 4.0f * cos(time * 0.5f)));
        model = glm::rotate(model, time, glm::vec3(0, 1, 0));
        glUniformMatrix4fv(uModelMatrix, 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(planet2.vao);
        glDrawElements(GL_TRIANGLES, planet2.indexCount, GL_UNSIGNED_INT, 0);

        // Moon orbiting Planet 2
        model = glm::translate(glm::mat4(1.0f), glm::vec3(4.0f * sin(time * 0.5f), 0.0f, 4.0f * cos(time * 0.5f)));
        model = glm::translate(model, glm::vec3(0.8f * sin(time * 3.0f), 0.0f, 0.8f * cos(time * 3.0f)));
        model = glm::rotate(model, time * 4.0f, glm::vec3(0, 1, 0));
        glUniformMatrix4fv(uModelMatrix, 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(moon.vao);
        glDrawElements(GL_TRIANGLES, moon.indexCount, GL_UNSIGNED_INT, 0);

        // Update time and swap buffers
        time += 0.016f; // ~60 FPS increment
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteProgram(program);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
