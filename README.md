### Updated Project Structure

```
xross/
├── src/                 # Source code
│   ├── main.cpp         # Main entry point
│   └── ...              # Other C++ source files
├── build/               # Build directory (generated files)
├── xross.pro            # Qt project file
└── Makefile             # Generated by qmake (used to compile)
```

### Step-by-Step Setup

#### 1. **Update `xross.pro` for Source & Build Directory**

You’ll need to tell **qmake** where your source files are located. This can be done by updating the `.pro` file to reflect your new `src/` directory for the source files and a separate `build/` directory for the build output.

#### `xross.pro`:

```pro
TEMPLATE = app
TARGET = xross
QT += core gui

# Set up the source directory
SOURCES += src/main.cpp  # This will include files from src directory

# Set up the build directory
DESTDIR = build  # This will tell qmake to put the build files in the 'build' directory

# If you have headers, you can specify them as well
HEADERS += src/other_header.h  # Add any header files as needed

```

#### 2. **Move `main.cpp` into `src/` directory**

Now, move your `main.cpp` into the `src/` directory:

```
xross/
├── src/
│   └── main.cpp
├── build/
├── xross.pro
└── Makefile
```

#### 3. **Re-run `qmake` and `make` to Build the Project**

1. First, clean the previous build files if you had already run `qmake` or `make` before:

   ```bash
   make clean
   ```

2. Then, run `qmake` to regenerate the necessary Makefile from your `xross.pro` file:

   ```bash
   qmake
   ```

3. Now, run `make` to build the project:
   ```bash
   make
   ```

After running these commands, the compiled application will be placed in the **`build/`** directory.

#### 4. **Running the Application**

Once compiled, you can run your application from the `build/` directory:

```bash
./build/xross
```

This should output:

```
Hello from Xross CLI!
```

### Next Steps

Now that you've set up your project structure with `src/` for source code and `build/` for compiled output, would you like to proceed with adding more features to your **CLI GUI** application, like:

1. **User input handling** (Command line arguments, interactive shell)?
2. **Implementing additional functionality** (e.g., executing commands, building the CLI)?
