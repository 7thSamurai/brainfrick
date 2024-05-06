# brainfrick

A simple [BrainF**k](https://en.wikipedia.org/wiki/Brainfuck) interpreter written in C for Linux.

Written for fun, cause why not!

## Building And Running

To build:

```
$ make
```

And then to run:

```
$ ./brainfrick [FILE PATH]  
```

Example test programs may be found in [/examples/](/examples/)

*Note: Either .b or .bf files may be used.*

## Commands

This implementation supports all 8 of the standard BrainF**K commands. All other characters are ignored.

| Character | Effect |
| --- | --- |
| `>` | Increments the data pointer by one. |
| `<` | Decrements the data pointer by one. |
| `+` | Increments the value at the data pointer by one. |
| `-` | Decrements the value at the data pointer by one. |
| `.` | Outputs one byte to standard output. |
| `,` | Reads one byte from standard input, storing it at the data-pointer. |
| `[` | Jumps forward to the command after the closing `]`, if the value at data-pointer is **zero**. Otherwise moves forward to next command. |
| `]` | Jumps backward to the command after the opening `[`, if the value at data-pointer is **non-zero**. Otherwise moves forward to next command. |

Please reference this [Wikipedia article](https://en.wikipedia.org/wiki/Brainfuck) for more information.

## Implementation Notes

- The cell size is 8 bits (One byte).
- The data array's length is initially 30000, but expands to the right infinitely (In increments of 3K).
- When the data pointer is at the far left, decrementing it causes it to wrap around to the end of the array.
- The number of nested jumps is limited to 4096 levels.

## Copyright

This software is licensed under MIT. Copyright © 2024 Zach Collins