# 🕒 Interactive Graphics Clock System

### CSE 426 | Computer Graphics Lab
### University of Asia Pacific

An OpenGL-based real-time analog clock visualization implementing classic Computer Graphics algorithms including Bresenham's Line Drawing Algorithm and Midpoint Circle Drawing Algorithm.

---

## 📸 Project Preview

![image alt](https://github.com/nhnadim06/Interactive-Graphics-Clock/blob/a4ce3ef7408962dd26873c78c0d77633e16a0aa3/clock-preview.jpg)

---

## 🚀 Project Overview

This project demonstrates the practical implementation of fundamental Computer Graphics algorithms through a real-time analog clock system. The application renders a fully functional clock synchronized with the system time while showcasing efficient raster graphics techniques using OpenGL and GLUT.

### Objectives

- Implement Bresenham's Line Drawing Algorithm
- Implement Midpoint Circle Drawing Algorithm
- Demonstrate real-time graphics rendering
- Practice OpenGL and GLUT programming
- Visualize system time using graphical primitives

---

## ✨ Features

- Real-time clock synchronized with system time
- Smooth hour, minute, and second hand animation
- Beautiful gradient background rendering
- Decorative orange/gold glow effect
- Hour and minute tick marks
- Numeric labels (1–12)
- Multi-thickness clock hands
- Efficient raster graphics algorithms
- Cross-platform compatibility

---

## 🧠 Algorithms Used

### 1. Bresenham's Line Drawing Algorithm

Used for:

- Clock hands
- Hour markers
- Minute markers

Advantages:

- Integer-only calculations
- High efficiency
- Smooth line rendering

---

### 2. Midpoint Circle Drawing Algorithm

Used for:

- Clock face
- Decorative glow rings
- Center hub
- Circular background effects

Advantages:

- Uses 8-way symmetry
- Reduced computational overhead
- Accurate circle rendering

---

## 🛠 Technology Stack

| Component | Technology |
|------------|------------|
| Language | C++11 |
| Graphics API | OpenGL |
| Window Toolkit | GLUT / FreeGLUT |
| IDE | Visual Studio Code |
| Compiler | GCC / Clang |

---

## 📂 Project Structure

```text
Interactive-Graphics-Clock/
│
├── interactive-clock.cpp
├── README.md
└── clock-preview.jpg/
```

---

## ⚙️ Build Instructions

### macOS

```bash
g++ -std=c++11 interactive-clock.cpp -o interactive-clock \
-framework OpenGL \
-framework GLUT \
-framework Cocoa \
-Wno-deprecated
```

Run:

```bash
./interactive-clock
```

---

### Linux

```bash
g++ -std=c++11 interactive-clock.cpp -o interactive-clock \
-lglut -lGL -lm
```

Run:

```bash
./interactive-clock
```

---

### Windows (MinGW)

```bash
g++ -std=c++11 interactive-clock.cpp -o interactive-clock.exe \
-lglut -lopengl32 -lgdi32
```

Run:

```bash
interactive-clock.exe
```

---

## 🎮 Usage

1. Compile the project.
2. Run the executable.
3. A 600×600 graphics window will appear.
4. The clock automatically synchronizes with the system time.
5. Observe real-time movement of hour, minute, and second hands.

---

## ⏱ Time Calculation Logic

### Second Hand

```text
360° ÷ 60 = 6° per second
```

### Minute Hand

```text
360° ÷ 60 = 6° per minute
```

Smooth interpolation:

```cpp
minuteAngle = minute * 6.0 + second * 0.1;
```

### Hour Hand

```text
360° ÷ 12 = 30° per hour
```

Smooth interpolation:

```cpp
hourAngle = hour * 30.0 + minute * 0.5 + second * (0.5 / 60.0);
```

---

## 🎨 Visual Design

### Window Configuration

| Property | Value |
|-----------|---------|
| Resolution | 600 × 600 |
| Clock Center | (300, 300) |
| Face Radius | 220 px |
| Outer Radius | 240 px |

### Color Scheme

| Element | Color |
|----------|---------|
| Background | Blue Gradient |
| Clock Face | White |
| Glow Ring | Orange / Gold |
| Hour Hand | White |
| Minute Hand | White |
| Second Hand | Red |
| Center Hub | White + Red |

---

## 📊 Performance

| Metric | Value |
|----------|----------|
| Refresh Interval | 1000 ms |
| Resolution | 600 × 600 |
| Memory Usage | < 5 MB |
| Graphics API | OpenGL 1.1+ |

### Optimization Techniques

- Bresenham integer arithmetic
- Midpoint circle symmetry
- Double buffering
- Timer-based rendering
- Efficient pixel-level drawing

---

## 🔮 Future Improvements

- Digital clock mode
- Alarm functionality
- Stopwatch feature
- Multiple timezone support
- Theme customization
- Mouse interaction
- Window resizing support
- Animated calendar integration

---

## 📚 Educational Concepts Demonstrated

- Computer Graphics Fundamentals
- Rasterization Techniques
- Bresenham Line Drawing
- Midpoint Circle Drawing
- OpenGL Rendering Pipeline
- Coordinate Transformations
- Real-Time Graphics Programming
- Event-Driven Programming

---

## 👨‍💻 Author

**Mohammad Nazmul Hossain Nadim**

Department of Computer Science & Engineering  
University of Asia Pacific

**Course:** CSE 426 – Computer Graphics Lab

**Supervisor:** Md. Rasheduzzaman  
Lecturer, Department of CSE  
University of Asia Pacific

---

## 📜 License

This project was developed for educational purposes as part of the **CSE 426 Computer Graphics Lab** course at the **University of Asia Pacific**.

Academic use is permitted with proper attribution.

---

⭐ If you found this project useful, consider giving the repository a star.
