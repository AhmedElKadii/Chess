#define DEFAULT_BOARD { \
    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}, \
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'}, \
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, \
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, \
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, \
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, \
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'}, \
    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}  \
}

#define CHECKMATE_BOARD { \
    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}, \
    {' ', 'P', 'P', 'P', 'P', 'P', 'P', 'P'}, \
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, \
    {' ', ' ', ' ', ' ', ' ', ' ', 'n', ' '}, \
    {' ', ' ', 'b', ' ', ' ', ' ', ' ', ' '}, \
    {' ', 'P', ' ', ' ', ' ', ' ', 'p', ' '}, \
    {'p', 'p', 'p', 'p', ' ', 'p', 'p', 'p'}, \
    {'r', 'n', 'b', 'q', 'k', ' ', ' ', 'r'}  \
}
