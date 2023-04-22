#include "new_structures.h"
#include "stdlib.h"


void randomize_board(struct config *conf) {
    int i, j;

    // Clear the board
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            conf->mat[i][j] = 0;
        }
    }

    // Place the pieces randomly
    int row, col, piece;
    for (piece = 0; piece < 6; piece++) { // 6 types of pieces
        int num_pieces = 0;
        while (num_pieces < 8) { // Place 8 pieces of each type
            row = rand() % 8;
            col = rand() % 8;
            if (conf->mat[row][col] == 0) { // If the square is empty
                if (piece == 0) { // Pawn
                    conf->mat[row][col] = rand() % 2 == 0 ? 'p' : -'p'; // Randomly assign black or white pawn
                } else if (piece == 1) { // Rook
                    conf->mat[row][col] = rand() % 2 == 0 ? 'r' : -'r'; // Randomly assign black or white rook
                } else if (piece == 2) { // Knight
                    conf->mat[row][col] = rand() % 2 == 0 ? 'q' : -'q'; // Randomly assign black or white knight
                } else if (piece == 3) { // Bishop
                    conf->mat[row][col] = rand() % 2 == 0 ? 'b' : -'b'; // Randomly assign black or white bishop
                } else if (piece == 4) { // Queen
                    conf->mat[row][col] = rand() % 2 == 0 ? 'q' : -'q'; // Randomly assign black or white queen
                } else { // King
                    conf->mat[row][col] = rand() % 2 == 0 ? 'k' : -'k'; // Randomly assign black or white king
                }
                num_pieces++;
            }
        }
    }

    
    conf->xrB = 0; conf->yrB = 4;
	conf->xrN = 7; conf->yrN = 4;

	conf->roqueB = 'r';
	conf->roqueN = 'r';

	conf->val = 0;
}