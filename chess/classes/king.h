#ifndef KING_H
#define KING_H

extern char whos_piece(wchar_t **board, int x, int y);

class King
{
    // private:
    //     const int value = 1;
    //     int initial_count = 8;

public:
    King() {};

    // Returns 'G' for a valid move or 'X' for an invalid move.
    char valid_move(wchar_t **board, int *move_coords)
    {
        // unpack array
        int x_source = move_coords[0];
        int y_source = move_coords[1];
        int x_dest = move_coords[2];
        int y_dest = move_coords[3];

        // is valid if source and dest are within one of each other, but not equal to each other
        if (x_source == x_dest && y_source == y_dest)
        {
            return 'X';
        }
        else if ((y_source + 1 == y_dest || y_source - 1 == y_dest || y_source == y_dest) && (x_source + 1 == x_dest || x_source - 1 == x_dest || x_source == x_dest))
        {
            return 'G';
        }
        return 'X';
    };

    // Return true if either king is not on the board. Otherwise return false
    bool is_taken(wchar_t **board, int BOARD_COLUMNS, int BOARD_ROWS)
    {
        bool is_white_king = false;
        bool is_black_king = false;
        for (int y = 0; y < BOARD_COLUMNS; y++)
        {
            for (int x = 0; x < BOARD_ROWS; x++)
            {
                if (board[y][x] == L'♔')
                {
                    is_white_king = true;
                }
                if (board[y][x] == L'♚')
                {
                    is_black_king = true;
                }
            }
        }
        return (!is_white_king || !is_black_king);
    }
};

#endif