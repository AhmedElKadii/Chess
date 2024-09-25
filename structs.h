#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

// Struct for a 2D vector
typedef struct {
    int x; // X coordinate
    int y; // Y coordinate
} vector2;

// Struct for a string (dynamic character array)
typedef struct {
    char *data;   // Pointer to the character array
    size_t length; // Length of the string
} string;

vector2 new_vector2(int x, int y);
string new_string(const char *initialData);
void free_string(string *str);
