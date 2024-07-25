#ifndef QUEEN_H
#define QUEEN_H

#include "./rook.h"
#include "./bishop.h"

extern char whos_piece(wchar_t **board, int x, int y);

class Queen : public Rook, public Bishop
{
    // private:
    //     const int value = 1;
    //     int initial_count = 8;

public:
    Queen() {};

    // Returns how the queen will move: vertical ('V'), horizontal ('H'), up-right ('P'), up-left ('Q'), down-right ('M'), down-left ('Z'), or invalid move ('X').
    char valid_move(wchar_t **board, int *move_coords)
    {
        // unpack array
        int x_source = move_coords[0];
        int y_source = move_coords[1];
        int x_dest = move_coords[2];
        int y_dest = move_coords[3];

        char move_a = Rook::valid_move(board, move_coords);
        char move_b = Bishop::valid_move(board, move_coords);

        if (move_a != 'X')
        {
            return move_a;
        }
        else if (move_b != 'X')
        {
            return move_b;
        }
        else
        {
            return 'X';
        }
    };
};

#endif