#pragma once
#include "types.hpp"
#include <vector>
class SquareSet{
private:
    Bitboard mask;
public:
    SquareSet(Bitboard m = 0);

    Bitboard get_mask();

    void add_square(Bitboard square);

    int size() const;

    std::vector<Square> iter() const;
};