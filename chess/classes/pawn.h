#ifndef PAWN_H
#define PAWN_H

extern char whos_piece(wchar_t **board, int x, int y);

class Pawn
{
    // private:
    //     const int value = 1;
    //     int initial_count = 8;

public:
    Pawn() {};

    // Returns how the pawn will move: one space forward (O), two spaces forward (T), diagonally (D), invalid move (X)
    char valid_move(wchar_t **board, int *move_coords, char opponent_turn)
    {
        // unpack array
        int x_source = move_coords[0];
        int y_source = move_coords[1];
        int x_dest = move_coords[2];
        int y_dest = move_coords[3];

        // a white pawn is moving
        if (opponent_turn == 'B')
        {
            // move up 1 space
            if ((y_source + 1 == y_dest) && (x_source == x_dest) && (whos_piece(board, x_dest, y_dest) == 'E'))
            {
                return 'O';
            }
            // attacking diagonal
            else if ((y_source + 1 == y_dest) && (x_source + 1 == x_dest || x_source - 1 == x_dest) && whos_piece(board, x_dest, y_dest) == opponent_turn)
            {
                return 'D';
            }
            // moving 2 spaces from baseline
            else if (y_source == 1 && y_dest == 3 && x_source == x_dest && (whos_piece(board, x_dest, 2) == 'E') && (whos_piece(board, x_dest, 3) == 'E'))
            {
                return 'T';
            }
        }

        // a black pawn is moving
        else if (opponent_turn == 'W')
        {
            // move up 1 space
            if ((y_source - 1 == y_dest) && (x_source == x_dest) && (whos_piece(board, x_dest, y_dest) == 'E'))
            {
                return 'O';
            }
            // attacking diagonal
            else if ((y_source - 1 == y_dest) && (x_source + 1 == x_dest || x_source - 1 == x_dest) && whos_piece(board, x_dest, y_dest) == opponent_turn)
            {
                return 'D';
            }
            // moving 2 spaces from baseline
            else if (y_source == 6 && y_dest == 4 && x_source == x_dest && (whos_piece(board, x_dest, 5) == 'E') && (whos_piece(board, x_dest, 4) == 'E'))
            {
                return 'T';
            }
        }
        return 'X';
    };

    bool is_promoted(int *move_coords)
    {
        if (move_coords[3] == 0 || move_coords[3] == 7)
        {
            return true;
        }
        return false;
    };

    void promote(wchar_t **board, int *move_coords, char player_turn)
    {
        // unpack array
        int x_source = move_coords[0];
        int y_source = move_coords[1];
        int x_dest = move_coords[2];
        int y_dest = move_coords[3];

        char exchange_pawn;
        while (exchange_pawn != 'Q' && exchange_pawn != 'K' && exchange_pawn != 'R' && exchange_pawn != 'B')
        {
            std::cout << "Promote your pawn into a Queen, Knight, Rook or Bishop (Q/K/R/B): ";
            std::cin >> exchange_pawn;
        }
        if (player_turn == 'W')
        {
            if (exchange_pawn == 'Q')
            {
                board[y_source][x_source] = L'♛';
            }
            else if (exchange_pawn == 'K')
            {
                board[y_source][x_source] = L'♞';
            }
            else if (exchange_pawn == 'R')
            {
                board[y_source][x_source] = L'♜';
            }
            else if (exchange_pawn == 'B')
            {
                board[y_source][x_source] = L'♝';
            }
        }
        else
        {
            if (exchange_pawn == 'Q')
            {
                board[y_source][x_source] = L'♕';
            }
            else if (exchange_pawn == 'K')
            {
                board[y_source][x_source] = L'♘';
            }
            else if (exchange_pawn == 'R')
            {
                board[y_source][x_source] = L'♖';
            }
            else if (exchange_pawn == 'B')
            {
                board[y_source][x_source] = L'♗';
            }
        }
    };
};

#endif