# 🤖 Robot Management System (C++ with PDCurses)

A **terminal-based application** to manage different types of robots such as **Line Follower**, **Maze Solver**, and **Drone**. Built entirely in **C++** using **Object-Oriented Programming** principles, this system uses **PDCurses** to deliver an interactive text-based user interface with keyboard-driven menus.

---

## 📌 Features

- 🧱 OOP-based modular design with inheritance
- 📋 Add, view, and modify parameters of various robots
- 📁 Each robot’s data saved in a separate `.txt` file
- 🧭 Keyboard navigation via arrow keys and `Enter`
- 🖼️ Menu system rendered using `curses.h` (PDCurses)
- 🧊 Cursor hidden for a clean interface

---

## 🛠️ Technologies Used

- **C++17**
- **PDCurses Library** for terminal UI
- Standard File I/O for data persistence

---

## ⚙️ Implementation Summary

The project defines a base class `Robot` with three derived classes:

- `LineFollower` — accepts speed and PID values
- `MazeSolver` — similar structure to Line Follower
- `Drone` — includes speed and 2D location coordinates

A `RobotManager` class maintains a collection of robots and allows:

- Adding new robots
- Displaying all existing robots
- Modifying parameters by searching with robot ID

The interface uses `curses.h` functions like `printw`, `scanw`, `getch`, `mvprintw`, `box`, etc., to render a navigable UI within the terminal.

---

## 🧩 File Overview

| File         | Description                                  |
|--------------|----------------------------------------------|
| `robolib.cpp`| Source code implementing the system          |
| `robolib.o`  | Object file generated during compilation      |
| `robolib.exe`| Executable for Windows (already compiled)    |
| `*.txt`      | Output files for each robot (auto-generated) |

---

## 💻 How to Compile and Build `.exe` (on Windows)

### ✅ Requirements

- MinGW (G++ compiler)
- PDCurses library (https://pdcurses.sourceforge.io/)

### ✅ Step-by-Step Setup

#### 1. Install MinGW
- Download from: https://osdn.net/projects/mingw/releases/
- Install components:
  - `mingw32-gcc-g++`
  - `mingw32-base`
- Add `C:\MinGW\bin` to your system PATH

#### 2. Install PDCurses
- Download PDCurses and extract
- Copy:
  - `curses.h`, `panel.h` → `C:\MinGW\include`
  - `pdcurses.a` → `C:\MinGW\lib`
  - `pdcurses.dll` → same folder as `.exe` OR `C:\Windows\System32`

#### 3. Compile the Program
In the folder where `robolib.cpp` is located, run:
```bash
g++ robolib.cpp -lpdcurses -o robolib.exe
This will generate robolib.exe in the same folder.
```

#### 4. Run the Program
```bash
robolib.exe
```

🧪 Example Interaction
Navigate menu with ↑ ↓ keys

Press Enter to select

Modify values with real-time terminal input

Each robot creates a *.txt file containing saved parameters

📸 Screenshots

![Screenshot 2025-06-23 124902](https://github.com/user-attachments/assets/4def8824-7e89-40c6-933e-e1463a9beb77)

![Screenshot 2025-06-23 125012](https://github.com/user-attachments/assets/ce726ea0-15c6-4120-99a9-3b2ecd1875a2)

![Screenshot 2025-06-23 125026](https://github.com/user-attachments/assets/c164f59d-2d15-4845-8ec3-09e82c4924c5)

![Screenshot 2025-06-23 125133](https://github.com/user-attachments/assets/4a929726-d6f5-4ea4-b00b-23e29f2a420b)


🪪 License
This project is licensed under the MIT License

🤝 Contributions
Pull requests and suggestions are welcome.
Raise issues here.

---
