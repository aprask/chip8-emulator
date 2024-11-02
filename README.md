# CHIP-8 Emulator

![image](https://github.com/user-attachments/assets/19246014-718a-49de-a460-ec5c99dd676e)

This project is a CHIP-8 emulator written in C, using the SDL2 library for graphics. It interprets and executes CHIP-8 bytecode, allowing users to run CHIP-8 programs as they would on vintage hardware. The emulator simulates all core components, including CPU instruction handling, memory, display, input, and timers.

## Features

- **CPU Emulation**: Executes CHIP-8 opcodes, handling jumps, calls, arithmetic, and drawing operations.
- **Memory Management**: Manages CHIP-8 memory, including program and stack.
- **Display**: Renders the CHIP-8 screen using SDL2.
- **Input Handling**: Simulates a 16-key hexadecimal keypad.
- **Timers**: Implements delay and sound timers.

## Requirements

- **SDL2**: Ensure SDL2 is installed on your system.

## Installation

1. Clone this repository:
   **git clone https://github.com/apraskal/chip8-emulator.git**

2. Navigate to the project directory:
   **cd chip8-emulator**

3. Build the project using CMake:
  **mkdir build && cd build**
  **cmake ..**
  **make**

4. Run the emulator with a CHIP-8 ROM file:
  **./chip8_emulator path/to/rom**

![image](https://github.com/user-attachments/assets/f411b65c-35c6-4660-a341-75d1df3c1094)

![image](https://github.com/user-attachments/assets/c21b6a33-08ef-400a-8131-af3d355abda1)

![image](https://github.com/user-attachments/assets/ea8a307d-6c8d-4619-964c-5095d8f7b308)

![image](https://github.com/user-attachments/assets/72c40bc1-f827-4974-9534-dfcf594765cf)
