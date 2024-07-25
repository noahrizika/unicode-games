#ifndef BISHOP_H
#define BISHOP_H

extern char whos_piece(wchar_t **board, int x, int y);

class Bishop
{
    // private:
    //     const int value = 1;
    //     int initial_count = 8;

public:
    Bishop() {};

    // Return 'P' for up-right  move, 'Q' for up-left move, 'M' for down-right move, 'Z' for down-left move, 'S' for a single-square move, or 'X' for an invalid move.
    char valid_move(wchar_t **board, int *move_coords)
    {
        // unpack array
        int x_source = move_coords[0];
        int y_source = move_coords[1];
        int x_dest = move_coords[2];
        int y_dest = move_coords[3];

        // moving diagonally up and right
        if (x_source + 1 <= 7 && y_source - 1 >= 0) // ensure piece won't move off the board
        {
            for (int x = x_source + 1, y = y_source - 1; x < x_dest && y > y_dest; x++, y--)
            {
                if (whos_piece(board, x, y) != 'E')
                {
                    return 'X';
                }
                if ((x == x_dest && y == y_dest) || (x + 1 == x_dest && y - 1 == y_dest))
                {
                    return 'P';
                }
            }
        }

        // moving diagonally up and left
        if (x_source - 1 >= 0 && y_source - 1 >= 0)
        {
            for (int x = x_source - 1, y = y_source - 1; x > x_dest && y > y_dest; x--, y--)
            {
                if (whos_piece(board, x, y) != 'E')
                {
                    return 'X';
                }
                if ((x == x_dest && y == y_dest) || (x - 1 == x_dest && y - 1 == y_dest))
                {
                    return 'Q';
                }
            }
        }

        // moving diagonally down and right
        if (x_source + 1 <= 7 && y_source + 1 <= 7)
        {
            for (int x = x_source + 1, y = y_source + 1; x < x_dest && y < y_dest; x++, y++)
            {
                if (whos_piece(board, x, y) != 'E')
                {
                    return 'X';
                }
                if ((x == x_dest && y == y_dest) || (x + 1 == x_dest && y + 1 == y_dest))
                {
                    return 'M';
                }
            }
        }

        // moving diagonally down and left
        if (x_source - 1 >= 0 && y_source + 1 <= 7)
        {
            for (int x = x_source - 1, y = y_source + 1; x > x_dest && y < y_dest; x--, y++)
            {
                if (whos_piece(board, x, y) != 'E')
                {
                    return 'X';
                }
                if ((x == x_dest && y == y_dest) || (x - 1 == x_dest && y + 1 == y_dest))
                {
                    return 'Z';
                }
            }
        }

        // handle one square moves
        if ((y_source + 1 == y_dest || y_source - 1 == y_dest) && (x_source + 1 == x_dest || x_source - 1))
        {
            return 'S';
        }

        return 'X';
    };
};

#endif