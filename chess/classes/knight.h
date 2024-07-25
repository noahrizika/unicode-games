#ifndef KNIGHT_H
#define KNIGHT_H

extern char whos_piece(wchar_t **board, int x, int y);

class Knight
{
    // private:
    //     const int value = 1;
    //     int initial_count = 8;

public:
    Knight() {};

    // Return 'L' for a valid rook move. Otherwise return invalid move 'X'.
    char valid_move(wchar_t **board, int *move_coords)
    {
        // unpack array
        int x_source = move_coords[0];
        int y_source = move_coords[1];
        int x_dest = move_coords[2];
        int y_dest = move_coords[3];

        // move in an L shape space
        if (((y_source + 2 == y_dest || y_source - 2 == y_dest) && ((x_source + 1 == x_dest) || (x_source - 1 == x_dest))) || ((x_source + 2 == x_dest || x_source - 2 == x_dest) && ((y_source + 1 == y_dest) || y_source - 1 == y_dest)))
        {
            return 'L';
        }
        else
        {
            return 'X';
        }
    };
};

#endif