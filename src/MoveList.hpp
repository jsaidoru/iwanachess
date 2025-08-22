#include "Move.hpp"
#include <iostream>

struct MoveList{
    Move moves[256]; // lowerbound of max number of possible moves is 218, buffered to 256 for safety
    int size = 0;

    Move* begin() { return moves; }
    Move* end()   { return moves + size; }

    const Move* begin() const { return moves; }
    const Move* end()   const { return moves + size; }

    void add_move(const Move& move);
    friend MoveList operator+(const MoveList& a, const MoveList& b);
    friend std::ostream& operator<<(std::ostream& os, const MoveList& list);
};