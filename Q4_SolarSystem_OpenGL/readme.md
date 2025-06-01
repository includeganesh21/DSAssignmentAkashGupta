# Q4: Mini Solar System Visualization using OpenGL

## 🧩 Problem Statement

Create a mini solar system visualization using OpenGL (ES 2.0+ or 3.0) that demonstrates your understanding of the graphics pipeline, transformations, and shaders.

---

## 🎯 Requirements

### Scene Rendering
- Render a **central Sun** that remains static at the center.
- Render at least **two planets** orbiting the Sun at different speeds and distances.
- One of the planets must have a **moon** orbiting it.

### Custom Shaders
- Write your own **vertex** and **fragment shaders** using GLSL.
- The **Sun** should have a shader-based **glow or pulsing effect**.
- Planets and moon can have **textures** or **gradient coloring** via shaders.

### Transformations & Animations
- Use **matrix transformations** to handle orbiting and rotation animations.
- Planets must **rotate on their axis** while orbiting the Sun.

### User Interaction
- Implement **camera controls**:
  - Rotate the view with **mouse drag** or **touch input**.
  - Optional: Zoom in/out with mouse scroll or pinch gestures.

### Performance
- The application should run smoothly at approximately **30 FPS or higher**.
- Use **VBOs/VAOs** or equivalent for rendering efficiency.

---

## 🔗 Solution Files

- [MiniSolarSystem.cpp](./MiniSolarSystem.cpp)  

---

## 🛠️ Build & Run Instructions in macOS

```bash
brew install glfw
brew install glew
brew install glm

# check installation
ls /opt/homebrew/include/GL/glew.h
ls /opt/homebrew/lib/libGLEW*

# Compile with appropriate OpenGL ES libraries and flags
clang++ -o solar_system solar_system.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -lglfw -lglew -framework OpenGL

# Run the application
./solar_system
```

## Output

[OUTPUT](./question4output.mov)
