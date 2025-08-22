#pragma once
#include <string>
#include "types.hpp"
#include <iostream>

class Move{
private:
    Square from_square;
    Square to_square;
    PieceType promotion;

    std::string square_to_coordinate(Square square) const {
        char file_char = 'a' + (static_cast<int>(square) % 8);
        char rank_char = '1' + (static_cast<int>(square) / 8);

        return std::string(1, file_char) + std::string(1, rank_char);
    }


public:
    Move();

    Move(Square from_sq, Square to_sq, PieceType promo = PieceType::PT_NONE)
        : from_square(from_sq), to_square(to_sq), promotion(promo) {}

    std::string to_uci() const {
        std::string from = square_to_coordinate(from_square);
        std::string to = square_to_coordinate(to_square);
        return from + to; // assume no promotion
    }

    friend std::ostream& operator<<(std::ostream& os, const Move& move);
};