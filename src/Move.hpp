#pragma once
#include <string>
#include "types.hpp"
#include <iostream>

class Move{
private:
    Square from_square;
    Square to_square;
    PieceType promotion;

    std::string square_to_coordinate(Square square) const;

public:
    Move();

    Move(Square from_sq, Square to_sq, PieceType promo = PieceType::PT_NONE)
        : from_square(from_sq), to_square(to_sq), promotion(promo) {}

    std::string to_uci() const;

    Square from() const {return from_square;}
    Square to() const {return to_square;}
    PieceType promotion_type() const {return promotion;}

    friend std::ostream& operator<<(std::ostream& os, const Move& move);
};