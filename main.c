#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interpreter.h"

int main(int argc, char **argv)
{
    // Check that the command line arguments are valid
    if (argc != 2)
    {
        printf("Usage: %s [FILE PATH]\n", argv[0]);

        return 1;
    }

    const char *path = argv[1];

    // Confirm that the file extension is valid
    const char *ext = strrchr(path, '.');
    if (!ext || (strcmp(ext, ".b") != 0 && strcmp(ext, ".bf") != 0))
    {
        printf("Invalid file extension, accepts .b or .bf\n");

        return 1;
    }

    // Attempt to open the file
    FILE *file = fopen(path, "r");
    if (!file)
    {
        printf("Failed to open file \"%s\"\n", path);

        return 1;
    }

    // Find the file's size
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // And read it's contents
    char *buffer = malloc(size);
    if (fread(buffer, sizeof(char), size, file) != size)
    {
        printf("Failed to read file \"%s\"\n", path);
        fclose(file);

        return 1;
    }

    fclose(file);

    // Create the interpreter from the program data
    InterpreterState *state = createInterpreter(buffer, size);
    
    free(buffer);
    if (!state)
        return 1;

    // Main loop
    while (1)
    {
        // Run the interpreter for once cycle
        int status = runInterpreter(state);

        // Error encountered
        if (status < 0)
        {
            deleteInterpreter(state);
            return 1;
        }

        // Program ended
        else if (!status)
            break;

    }

    // Clean up
    deleteInterpreter(state);

    return 0;
}