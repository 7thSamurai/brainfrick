#pragma once

#include <stdint.h>

// A single instruction
typedef struct
{
    char command;

    // Only used for Jump commands
    unsigned int jumpTarget;
} Instruction;

// Interpreter state information
typedef struct
{
    // Input program data
    Instruction *program;
    unsigned int programSize;

    // Working data array
    uint8_t *data;
    unsigned int dataSize;

    // Registers
    unsigned int programCounter;
    unsigned int dataPointer;

} InterpreterState;

// Creates a interpreter state
// Returns NULL on error
InterpreterState *createInterpreter(const char *programBuffer, unsigned int programBufferSize);

// Deletes a interpreter state
void deleteInterpreter(InterpreterState *state);
