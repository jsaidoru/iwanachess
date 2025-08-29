#include "Move.hpp"
#include "MoveList.hpp"
#include <iostream>

void MoveList::add_move(const Move& move){
    moves[size++] = move;
}

MoveList operator+(const MoveList& a, const MoveList& b) {
    MoveList result;
    result.size = a.size + b.size;

    for (int i = 0; i < a.size; i++)
        result.moves[i] = a.moves[i];

    for (int i = 0; i < b.size; i++)
        result.moves[a.size + i] = b.moves[i];

    return result;
}

std::ostream& operator<<(std::ostream& os, const MoveList& list){
    for (Move move : list){
        os << move.to_uci() << "\n";
    }
    return os;
}