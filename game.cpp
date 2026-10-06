#include "game.h"

#include <algorithm>
#include <limits>

const int LINES[8][3] = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
    {0, 4, 8}, {2, 4, 6}};

char winner(const Board &b) {
    for (const auto &l : LINES)
        if (b[l[0]] != EMPTY && b[l[0]] == b[l[1]] && b[l[1]] == b[l[2]])
            return b[l[0]];
    return EMPTY;
}

bool isFull(const Board &b) {
    return std::none_of(b.begin(), b.end(), [](char c) { return c == EMPTY; });
}

int minimax(Board &b, int depth, bool aiTurn, int alpha, int beta) {
    char w = winner(b);
    if (w == AI) return 10 - depth;
    if (w == HUMAN) return depth - 10;
    if (isFull(b)) return 0;

    if (aiTurn) {
        int best = std::numeric_limits<int>::min();
        for (int i = 0; i < 9; ++i) {
            if (b[i] != EMPTY) continue;
            b[i] = AI;
            best = std::max(best, minimax(b, depth + 1, false, alpha, beta));
            b[i] = EMPTY;
            alpha = std::max(alpha, best);
            if (beta <= alpha) break;
        }
        return best;
    }

    int best = std::numeric_limits<int>::max();
    for (int i = 0; i < 9; ++i) {
        if (b[i] != EMPTY) continue;
        b[i] = HUMAN;
        best = std::min(best, minimax(b, depth + 1, true, alpha, beta));
        b[i] = EMPTY;
        beta = std::min(beta, best);
        if (beta <= alpha) break;
    }
    return best;
}

int bestMove(Board &b) {
    int bestScore = std::numeric_limits<int>::min();
    int move = -1;
    for (int i = 0; i < 9; ++i) {
        if (b[i] != EMPTY) continue;
        b[i] = AI;
        int score = minimax(b, 1, false,
                            std::numeric_limits<int>::min(),
                            std::numeric_limits<int>::max());
        b[i] = EMPTY;
        if (score > bestScore) {
            bestScore = score;
            move = i;
        }
    }
    return move;
}