#ifndef GAME_H
#define GAME_H

#include <array>

using Board = std::array<char, 9>;

const char EMPTY = ' ';
const char HUMAN = 'X';
const char AI = 'O';

char winner(const Board &b);
bool isFull(const Board &b);
int minimax(Board &b, int depth, bool aiTurn, int alpha, int beta);
int bestMove(Board &b);

#endif