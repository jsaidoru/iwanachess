#include "types.hpp"
#include "Move.hpp"
#include <string>
#include <iostream>

std::string Move::square_to_coordinate(Square square) const {
    char file_char = 'a' + (static_cast<int>(square) % 8);
    char rank_char = '1' + (static_cast<int>(square) / 8);

    return std::string(1, file_char) + std::string(1, rank_char);
}



Move::Move() : from_square(Square::NO_SQ), to_square(Square::NO_SQ), promotion(PieceType::PT_NONE) {}

std::string Move::to_uci() const {
    std::string from = square_to_coordinate(from_square);
    std::string to = square_to_coordinate(to_square);
    return from + to; // assume no promotion
}

std::ostream& operator<<(std::ostream& os, const Move& move){
    os << move.to_uci();
    return os;
}