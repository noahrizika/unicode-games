#ifndef ROOK_H
#define ROOK_H

extern char whos_piece(wchar_t **board, int x, int y);

class Rook
{
    // private:
    //     const int value = 1;
    //     int initial_count = 8;

public:
    Rook() {};

    // Return 'U' for moving upward, 'D' for downards, 'L' for horizontally to the left, 'R' for horizontally to the right, 'S' for a single-square move, or 'X' for an invalid move.
    char valid_move(wchar_t **board, int *move_coords)
    {
        // unpack array
        int x_source = move_coords[0];
        int y_source = move_coords[1];
        int x_dest = move_coords[2];
        int y_dest = move_coords[3];

        // moving horizontally to the right
        if (x_source < 7)
        {
            for (int x = x_source + 1; x < x_dest; x++)
            {
                if (whos_piece(board, x, y_source) != 'E')
                {
                    break;
                }
                if ((x == x_dest || x + 1 == x_dest) && y_source == y_dest)
                {
                    return 'R';
                }
            }
        }

        // moving horizontally to the left
        if (x_source > 0)
        {
            for (int x = x_source - 1; x > x_dest; x--)
            {
                if (whos_piece(board, x, y_source) != 'E')
                {
                    break;
                }
                if ((x == x_dest || x - 1 == x_dest) && y_source == y_dest)
                {
                    return 'L';
                }
            }
        }

        // moving downward (increasing y)
        if (y_source < 7)
        {
            for (int y = y_source + 1; y < y_dest; y++)
            {
                if (whos_piece(board, x_dest, y) != 'E')
                {
                    break;
                }
                if ((y == y_dest || y + 1 == y_dest) && x_source == x_dest)
                {
                    return 'D';
                }
            }
        }

        // moving upward (decreasing y)
        if (y_source > 0)
        {
            for (int y = y_source - 1; y > y_dest; y--)
            {
                if (whos_piece(board, x_dest, y) != 'E')
                {
                    break;
                }
                if ((y == y_dest || y - 1 == y_dest) && x_source == x_dest)
                {
                    return 'U';
                }
            }
        }

        //  handle one space moves
        else if (((y_source + 1 == y_dest || y_source - 1 == y_dest) && x_source == x_dest) || ((x_source + 1 == x_dest || x_source - 1 == x_dest) && y_source == y_dest))
        {
            return 'S';
        }

        return 'X';
    };
};

#endif