#include <cstdlib>
#include <iostream>
#include <limits>

#include "game.h"

void printBoard(const Board &b) {
    std::cout << "\n";
    for (int r = 0; r < 3; ++r) {
        std::cout << " ";
        for (int c = 0; c < 3; ++c) {
            int i = r * 3 + c;
            std::cout << (b[i] == EMPTY ? char('1' + i) : b[i]);
            if (c < 2) std::cout << " | ";
        }
        std::cout << "\n";
        if (r < 2) std::cout << "---+---+---\n";
    }
    std::cout << "\n";
}

int readHumanMove(const Board &b) {
    while (true) {
        std::cout << "Your move (1-9): ";
        int m;
        if (!(std::cin >> m)) {
            if (std::cin.eof()) std::exit(0);
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a number.\n";
            continue;
        }
        if (m < 1 || m > 9)
            std::cout << "Choose a number from 1 to 9.\n";
        else if (b[m - 1] != EMPTY)
            std::cout << "That square is taken.\n";
        else
            return m - 1;
    }
}

int main() {
    std::cout << "=== Tic-Tac-Toe: Human (X) vs AI (O) ===\n";

    char again = 'y';
    while (again == 'y' || again == 'Y') {
        Board board;
        board.fill(EMPTY);

        std::cout << "\nDo you want to go first? (y/n): ";
        char first;
        std::cin >> first;
        bool humanTurn = (first == 'y' || first == 'Y');

        printBoard(board);

        while (winner(board) == EMPTY && !isFull(board)) {
            if (humanTurn) {
                board[readHumanMove(board)] = HUMAN;
            } else {
                int m = bestMove(board);
                board[m] = AI;
                std::cout << "AI plays " << (m + 1) << "\n";
            }
            printBoard(board);
            humanTurn = !humanTurn;
        }

        char w = winner(board);
        if (w == AI)
            std::cout << "AI wins!\n";
        else if (w == HUMAN)
            std::cout << "You win!\n";
        else
            std::cout << "It's a draw.\n";

        std::cout << "\nPlay again? (y/n): ";
        std::cin >> again;
    }
    return 0;
}