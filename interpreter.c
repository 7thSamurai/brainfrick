#include "interpreter.h"

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

// Initial data array size in bytes
#define INITIAL_DATA_SIZE 30000

InterpreterState *createInterpreter(char *programBuffer, unsigned int programBufferSize)
{
    InterpreterState *state = malloc(sizeof(InterpreterState));

    // Copy over the program data
    state->program = programBuffer;
    state->programSize = programBufferSize;

    // Create the working array data buffer
    state->data = malloc(INITIAL_DATA_SIZE);
    state->dataSize = INITIAL_DATA_SIZE;
    memset(state->data, 0x00, INITIAL_DATA_SIZE);

    // Initial pointer values
    state->programCounter = 0;
    state->dataPointer = 0;

    return state;
}

void deleteInterpreter(InterpreterState *state)
{
    // Clean up
    if (state)
    {
        if (state->program)
            free(state->program);

        if (state->data)
            free(state->data);

        free(state);
    }
}