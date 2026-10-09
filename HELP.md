# Line Editor Help

The editor works on numbered lines in a terminal. Start it after compiling `line_editor.c`.

| Command | What it does | Example |
|---|---|---|
| `i` or `insert` | Insert a line at a position from 1 through the current line count + 1 | Type `i`, enter `2`, then enter the text |
| `d` or `delete` | Delete an existing line | Type `d`, then enter `2` |
| `p`, `print`, or `display` | Display all lines with their line numbers | Type `p` |
| `s` or `save` | Save the current document to a text file | Type `s`, then `document.txt` |
| `l` or `load` | Load a text file, replacing the current in-memory document | Type `l`, then `document.txt` |
| `f` or `search` | Find text and print matching line numbers | Type `f`, then `Hello` |
| `h` or `help` | Show the built-in help | Type `h` |
| `q` or `quit` | Exit the editor | Type `q` |

## Notes

- Line numbers start at 1.
- Inserting at line 1 places text at the beginning; inserting at the end + 1 appends it.
- Invalid line numbers are rejected.
- Loading a file replaces the current document.
- The editor stores at most 500 lines, with a maximum of 255 characters per line.
