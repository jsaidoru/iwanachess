#include <vector>
#include <iostream>
#include "SquareSet.hpp"
#include "types.hpp"

// A wrapper around bitboards, provide an iterable interface and other convenience methods.
Bitboard mask;
std::vector<Bitboard> squares;

SquareSet::SquareSet(Bitboard m) : mask(m) {}

Bitboard SquareSet::get_mask() const{
    return mask;
}

void SquareSet::add_square(Bitboard square){
    mask |= (1ull << square);
}

int SquareSet::size() const {
    return __builtin_popcountll(mask);
}

Square SquareSet::Iterator::operator*() {
    return static_cast<Square>(__builtin_ctzll(remaining));
}

SquareSet::Iterator &SquareSet::Iterator::operator++() {
    remaining &= (remaining - 1);
    return *this;
}

bool SquareSet::Iterator::operator!=(const SquareSet::Iterator &other) {
    return remaining != other.remaining;
}

std::ostream& operator<<(std::ostream& os, const SquareSet& squareset) {
    os << std::hex << squareset.get_mask();
    return os;
}

SquareSet operator|(const SquareSet& lhs, const SquareSet& rhs) {
    return SquareSet(lhs.get_mask() | rhs.get_mask());
}