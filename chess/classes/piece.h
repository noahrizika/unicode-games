#ifndef PIECE_H
#define PIECE_H

extern char whos_piece(wchar_t **board, int x, int y);

// later make a Piece class and have each piece extend it. valid_move could be overloaded (?)
class Piece
{
    // private:
    //     int value;
    //     int initial_count;

public:
    Piece() {};

    // unequivocally swap two of the board's elements
    void move(wchar_t **board, int *move_coords, char move_type)
    {
        // unpack array
        int x_source = move_coords[0];
        int y_source = move_coords[1];
        int x_dest = move_coords[2];
        int y_dest = move_coords[3];

        // is destination a piece or empty?
        wchar_t destination = board[y_dest][x_dest];

        // move piece to destination
        board[y_dest][x_dest] = board[y_source][x_source];

        // determine the source square's color
        if ((x_source % 2 == 0 && y_source % 2 == 0) || (x_source % 2 != 0 && y_source % 2 != 0))
        {
            board[y_source][x_source] = L'░';
        }
        else
        {
            board[y_source][x_source] = L'█';
        }
    }
};
#endif