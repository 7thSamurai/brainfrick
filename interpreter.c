#include "interpreter.h"

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

// Initial data array size in bytes
#define INITIAL_DATA_SIZE 30000

InterpreterState *createInterpreter(const char *programBuffer, unsigned int programBufferSize)
{
    InterpreterState *state = malloc(sizeof(InterpreterState));

    // Copy over the program data
    state->program = malloc(programBufferSize * sizeof(Instruction));
    state->programSize = programBufferSize;

    // Create the working array data buffer
    state->data = malloc(INITIAL_DATA_SIZE);
    state->dataSize = INITIAL_DATA_SIZE;
    memset(state->data, 0x00, INITIAL_DATA_SIZE);

    // Initial pointer values
    state->programCounter = 0;
    state->dataPointer = 0;


    // Jump stack stuff
    const unsigned int jumpStackSize = 4096;
    unsigned int jumpStack[jumpStackSize];
    unsigned int jumpStackPointer = 0;



    // Copy over the program data
    for (unsigned int pos = 0; pos < programBufferSize; pos++)
    {
        // Copy the command
        state->program[pos].command = programBuffer[pos];

        // Handle precalculating the jumps
        if (programBuffer[pos] == '[')
        {
            // Make sure that the jump stack is not full
            if (jumpStackPointer >= jumpStackSize)
            {
                printf("Exceeded the interpreter's maximum allowed number of nested jumps (max %u)", jumpStackSize);

                deleteInterpreter(state);
                return NULL;
            }

            // Push
            jumpStack[jumpStackPointer++] = pos;
        }

        else if (programBuffer[pos] == ']')
        {
            // Make sure that the jump stack is not empty
            if (!jumpStackPointer)
            {
                printf("Missing opening bracket. Closing bracket at position 0x%x\n", pos);

                deleteInterpreter(state);
                return NULL;
            }

            // Pop
            unsigned int opening = jumpStack[--jumpStackPointer];

            // Store each other's position
            state->program[pos].jumpTarget = opening;
            state->program[opening].jumpTarget = pos;
        }
    }

    // Make sure that all the jump brackets were closed
    if (jumpStackPointer)
    {
        while (jumpStackPointer--)
        {
            printf("Missing closing bracket. Opening bracket at position 0x%x\n", jumpStack[jumpStackPointer]);
        }

        deleteInterpreter(state);
        return NULL;
    }

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
