# Simple Line Editor in C

A small terminal-based line editor built for the **Build a Simple Line Editor in C** coding competition. It keeps up to 500 lines in memory, with up to 255 characters per line.

## Features

- Insert a line at a selected line number
- Delete a line by number
- Display the document with line numbers
- Save the document to a text file
- Load a text file into the editor
- Search for text and report matching line numbers

## Requirements

- GCC (MinGW-w64/MSYS2 on Windows, or GCC on Linux/macOS)
- A terminal

## Compile and run

```sh
gcc -std=c11 -Wall -Wextra -pedantic line_editor.c -o line_editor
```

On Linux/macOS:

```sh
./line_editor
```

On Windows (PowerShell):

```powershell
.\line_editor.exe
```

## Quick demo

1. Run the program and type `i` to insert a line.
2. Enter line number `1`, then type `Hello, world!`.
3. Type `p` to display the document.
4. Type `s` and enter `document.txt` to save.
5. Type `q` to quit.

See [HELP.md](HELP.md) for the command reference.

## Design

The editor uses a fixed two-dimensional character array (`lines[MAX_LINES][MAX_LEN]`). This is straightforward for a short classroom exercise and makes insert/delete shifting easy to demonstrate. Its trade-off is a fixed capacity and fixed maximum line length.
