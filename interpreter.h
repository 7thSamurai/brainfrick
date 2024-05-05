#pragma once

#include <stdint.h>

// Interpreter state information
typedef struct
{
    // Input program data
    char *program;
    unsigned int programSize;

    // Working data array
    uint8_t *data;
    unsigned int dataSize;

    // Registers
    unsigned int programCounter;
    unsigned int dataPointer;

} InterpreterState;

// Creates a interpreter state (Takes ownership of the program array)
InterpreterState *createInterpreter(char *programBuffer, unsigned int programBufferSize);

// Deletes a interpreter state
void deleteInterpreter(InterpreterState *state);
