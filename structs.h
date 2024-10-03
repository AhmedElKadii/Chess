#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#include "settings.h"

// Struct for a 2D vector
typedef struct {
    int x; // X coordinate
    int y; // Y coordinate
} vector2;

vector2 new_vector2(int x, int y);
bool equals(vector2 v1, vector2 v2);
