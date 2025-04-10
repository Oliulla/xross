---

# Xross CLI Documentation

## Installation

### Step 1: Clone the Repository

Clone the repository from GitHub:

```bash
git clone https://github.com/yourusername/xross-cli.git
cd xross-cli
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

You can input commands like `ls`, `dr`, or any other text to see the response.

### GUI Usage

To use the GUI version, simply run:

```bash
./build/xross
```

The application window will appear, allowing you to enter commands and view the results.

---
