# Paper Design — Simple Line Editor

## Data structure
Use a fixed array of strings: `char lines[500][256]` and an integer `line_count`.

**Reason:** it is easy to explain and implement in a short exercise. Each line has a fixed capacity, and insertion/deletion shifts later lines.

## Command set
- `i`: insert line at a numbered position
- `d`: delete numbered line
- `p`: display all lines
- `s`: save to a text file
- `l`: load from a text file
- `f`: search text
- `h`: help
- `q`: quit

## Core logic
- **Insert:** validate position, shift lines right from the end, copy new text into the open slot, increment count.
- **Delete:** validate position, shift subsequent lines left, decrement count.
- **Display:** print each line with its 1-based line number.

This file documents the intended design; if the assignment requires hand-written paper evidence, prepare and submit your own paper sketch/photo as instructed by the course.
