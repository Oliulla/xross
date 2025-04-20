# Xross Terminal Documentation

## Purpose

**Xross Terminal** is an open-source cross-platform terminal interface designed to unify the command-line experience across different operating systems and kernels. Whether you're on Windows (using PowerShell or CMD), Linux, or macOS, Xross ensures that common commands like `ls`, `dir`, `cd`, and others behave consistently.

This project was born out of the frustration developers face when switching between operating systems and having to remember OS-specific commands. Xross bridges that gap by interpreting the command context and providing the appropriate response, regardless of the system you're on.

🧩 The goal is to create a universal CLI/GUI terminal experience where:

- `dir`, `ls`, or `Get-ChildItem` show the same result.
- Developers can use familiar commands across all platforms.
- Community contributors can easily add or map new commands from different shells.

We welcome contributions to help expand this cross-platform compatibility and make terminal life easier for everyone.

## Installation

### Step 1: Clone the Repository

Clone the repository from GitHub:

```bash
git clone https://github.com/Oliulla/xross.git
cd xross
```

### Step 2: Install Dependencies

Make sure you have Qt and the necessary build tools installed. You can install them using:

```bash
sudo apt update
sudo apt install qtbase5-dev g++
```

### Step 3: Build the Application

Use `qmake` to configure the project and `make` to build it:

```bash
qmake
make
```

The compiled executable will be located in the `build/` directory.

## Usage

### CLI Usage

Run the CLI application from the terminal:

```bash
./build/xross
```

You can input commands like `help`, `pwd`, `cd`, or `clear` and get a normalized response regardless of your OS.

### GUI Usage

To use the GUI version, simply run:

```bash
./build/xross
```

### Project Structure

```
xross/
│
├── src/
│   ├── main.cpp
│   └── commands
|          └──── // Command header files
│
├── build/                // Build directory
│   └── (compiled files)
│
├── xross.pro             // Qt project file
├── README.md             // Documentation file
└── .gitignore            // Git ignore file
```
