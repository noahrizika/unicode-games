#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cwchar>

// include chess piece classes
#include "./classes/piece.h"
#include "./classes/pawn.h"
#include "./classes/rook.h"
#include "./classes/knight.h"
#include "./classes/bishop.h"
#include "./classes/queen.h"
#include "./classes/king.h"

// include these so console can print unicode
#include <locale>
#include <codecvt>

#define BOARD_ROWS 8
#define BOARD_COLUMNS 8

using namespace std;

wchar_t **init_board();
void print_board(wchar_t **board);
int *get_move(wchar_t **board, char player_turn);
char whos_piece(wchar_t **board, int x, int y);
bool can_enact_move(wchar_t **board, int *move_coords, char player_turn, char opponent_turn, Piece piece, Pawn pawn, Rook rook, Knight knight, Bishop bishop, Queen queen, King king);

// **add a feature for pawn -> x once it gets to the other side of the board
// **add ascii animations for each kind of move (castling, taking a piece, maybe also just moving) and play them when relevant, so its like wizard's chess

int main(void)
{
    // enable console to print unicode
    locale::global(locale("en_US.UTF-8"));
    wcout.imbue(locale());

    // initialize lasting game variables
    bool game_over;
    bool can_move;
    Piece piece;
    Pawn pawn;
    Rook rook;
    Knight knight;
    Bishop bishop;
    Queen queen;
    King king;
    char play_again = 'y';

    while (play_again == 'y')
    {
        // initialize current game variables
        game_over = false;
        char player_turn = 'W';
        char opponent_turn = 'B';
        wchar_t **board = init_board();
        int *move_coords = nullptr;

        cout << endl
             << endl
             << "This game is meant to be played with a black background (otherwise black pieces will look like white pieces and vice versa)" << endl;

        while (!game_over)
        {
            print_board(board);
            cout << "Player's Turn: " << player_turn << endl;

            can_move = false;
            do
            {
                move_coords = get_move(board, player_turn);
                if (move_coords != nullptr)
                {
                    can_move = can_enact_move(board, move_coords, player_turn, opponent_turn, piece, pawn, rook, knight, bishop, queen, king);
                }
            } while (!can_move);

            swap(player_turn, opponent_turn);

            game_over = king.is_taken(board, BOARD_COLUMNS, BOARD_ROWS);
        }
        print_board(board);

        if (opponent_turn == 'W')
        {
            cout << "White Wins!" << endl;
        }
        else
        {
            cout << "Black Wins!" << endl;
        }

        cout << "Play again? (y/n): ";
        cin >> play_again;

        // free memory in the heap
        delete[] board[0];
        delete[] board;
        delete[] move_coords;
    }

    return 0;
}

// Build the board using unicode chess pieces (White: ♜♞♝♛♚♟ | Black: ♖♘♗♕♔♙). Index board via board[y][x].
wchar_t **init_board()
{
    wchar_t **board = new wchar_t *[BOARD_ROWS];
    board[0] = new wchar_t[BOARD_ROWS * BOARD_COLUMNS];
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        board[i] = board[0] + i * BOARD_COLUMNS;
    }

    wcscpy(board[0], L"♜♞♝♛♚♝♞♜");
    wcscpy(board[1], L"♟♟♟♟♟♟♟♟");
    wcscpy(board[2], L"░█░█░█░█");
    wcscpy(board[3], L"█░█░█░█░");
    wcscpy(board[4], L"░█░█░█░█");
    wcscpy(board[5], L"█░█░█░█░");
    wcscpy(board[6], L"♙♙♙♙♙♙♙♙");
    wcscpy(board[7], L"♖♘♗♕♔♗♘♖");

    return board;
}

void print_board(wchar_t **board)
{
    cout << endl;
    cout << "  ABCDEFGH" << endl;
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        cout << i << " ";
        for (int j = 0; j < BOARD_COLUMNS; j++)
        {
            wcout << board[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

// Returns a pointer to 4 integers: x_source (0), y_source (1), x_dest (2), y_dest (3)
int *get_move(wchar_t **board, char player_turn)
{
    string move;

    // incorrect input if: incorrect number of inputs, coords are too large or small, source is not player's piece, destination is player's piece
    while (size(move) != 5 || (int(move[0]) - 65) >= BOARD_ROWS || (int(move[0]) - 65) < 0 || int(move[1] - 48) >= BOARD_COLUMNS || int(move[1] - 48) < 0 || whos_piece(board, (int(move[0]) - 65), (move[1] - 48)) != player_turn || whos_piece(board, (int(move[3]) - 65), (move[4] - 48)) == player_turn)
    {
        cout << "What is your move? (ie: B3,B5): ";
        cin >> move;
        // cout << "move: " << move << " int(move[0]) - 65: " << int(move[0]) - 65 << " move[1]: " << int(move[1]) - 48 << " int(move[3] - 65): " << int(move[3]) - 65 << " move[4]: " << int(move[4]) - 48 << endl;
    }

    int *move_coords = new int[4];
    move_coords[0] = int(move[0]) - 65; // x_source
    move_coords[1] = int(move[1]) - 48; // y_source
    move_coords[2] = int(move[3]) - 65; // x_dest
    move_coords[3] = int(move[4]) - 48; // y_dest

    return move_coords;
}

// Returns 'W' for white, 'B' for black, 'E' for empty, 'X' or 'Y' for respective, out of bounds coordinates of x or y (and couts an explanation for out of bound coordinates)
char whos_piece(wchar_t **board, int x, int y)
{
    if (x >= BOARD_ROWS || x < 0)
    {
        cout << "x coordinate is out of bounds" << endl;
        return 'X';
    }
    if (y >= BOARD_COLUMNS || y < 0)
    {
        cout << "y coordinate is out of bounds" << endl;
        return 'Y';
    }
    if (board[y][x] == L'♜' || board[y][x] == L'♞' || board[y][x] == L'♝' || board[y][x] == L'♛' || board[y][x] == L'♚' || board[y][x] == L'♟')
    {
        return 'W';
    }
    else if (board[y][x] == L'♖' || board[y][x] == L'♘' || board[y][x] == L'♗' || board[y][x] == L'♕' || board[y][x] == L'♔' || board[y][x] == L'♙')
    {
        return 'B';
    }
    return 'E';
}

// Checks if the inputted move is valid for the selected piece. Conducts the move if valid and returns true, otherwise returns false.
bool can_enact_move(wchar_t **board, int *move_coords, char player_turn, char opponent_turn, Piece piece, Pawn pawn, Rook rook, Knight knight, Bishop bishop, Queen queen, King king)
{
    char move;
    switch (board[move_coords[1]][move_coords[0]])
    {
    case (L'♙'):
    case (L'♟'):
        move = pawn.valid_move(board, move_coords, opponent_turn);
        if (move != 'X' && pawn.is_promoted(move_coords))
        {
            pawn.promote(board, move_coords, player_turn);
        }
        break;
    case (L'♖'):
    case (L'♜'):
        move = rook.valid_move(board, move_coords);
        break;
    case (L'♘'):
    case (L'♞'):
        move = knight.valid_move(board, move_coords);
        break;
    case (L'♗'):
    case (L'♝'):
        move = bishop.valid_move(board, move_coords);
        break;
    case (L'♕'):
    case (L'♛'):
        move = queen.valid_move(board, move_coords);
        break;
    case (L'♔'):
    case (L'♚'):
        move = king.valid_move(board, move_coords);
        break;
    default:
        return false;
    }
    if (move == 'X')
    {
        return false;
    }
    piece.move(board, move_coords, move);
    return true;
}
