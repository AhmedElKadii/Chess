#include "structs.h"

// Function to initialize a Vector2
vector2 new_vector2(int x, int y) {
    vector2 vec;
    vec.x = x;
    vec.y = y;
    return vec;
}

bool equals(vector2 v1, vector2 v2) {
	return v1.x == v2.x && v1.y == v2.y;
}
