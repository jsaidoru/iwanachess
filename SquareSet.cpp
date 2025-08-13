#include <vector>
#include <iostream>
#include "SquareSet.hpp"
#include "types.hpp"

Bitboard mask;
std::vector<Bitboard> squares;

SquareSet::SquareSet(Bitboard m) : mask(m) {}

Bitboard SquareSet::get_mask(){
    return mask;
}

void SquareSet::add_square(Bitboard square){
    mask |= (1ull << square);
}

int SquareSet::size() const {
    return __builtin_popcountll(mask);
}

std::vector<Square> SquareSet::iter() const {
    std::vector<Square> squares;
    uint64_t m = mask;
    while (m) {
        int sq = __builtin_ctzll(m);
        squares.push_back(sq);
        m &= (m - 1);
    }
    return squares;
}