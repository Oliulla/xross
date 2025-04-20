# Xross Terminal Documentation

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

You can input commands like `ls`, `dr`, or any other text to see the response.

### GUI Usage

To use the GUI version, simply run:

```bash
./build/xross
```

### Project Structure

```
xross-cli/
│
├── src/
│   ├── main.cpp
│   ├── MainWindow.h
│   ├── MainWindow.cpp
│   ├── TerminalDisplay.h
│   └── TerminalDisplay.cpp
│
├── build/                // Build directory
│   └── (compiled files)
│
├── xross.pro             // Qt project file
├── README.md             // Documentation file
└── .gitignore            // Git ignore file
```

```c++
// commands/ClearCommand.h
#ifndef CLEARCOMMAND_H
#define CLEARCOMMAND_H

#include "ICommand.h"

class ClearCommand : public ICommand {
public:
    QString name() const override {
        return "clear";
    }

    QString execute(const QStringList &args) override {
        Q_UNUSED(args);
        return QString("__CLEAR__");  // special signal to terminal
    }
};

#endif // CLEARCOMMAND_H

```
