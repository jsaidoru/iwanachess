#pragma once
#include "types.hpp"
#include <vector>
#include <ostream>
class SquareSet{
private:
    Bitboard mask;
public:
    SquareSet(Bitboard m = 0);

    Bitboard get_mask() const;

    void add_square(Bitboard square);

    int size() const;

    class Iterator {
    private:
        Bitboard remaining;
    public:
        explicit Iterator(Bitboard m) : remaining(m) {}

        Square operator*();

        Iterator& operator++();

        bool operator!=(const Iterator& other);
    };

    // begin() and end()
    Iterator begin() const{
        return Iterator(mask);
    }

    Iterator end() const { 
        return Iterator(0); 
    }

    friend std::ostream& operator<<(std::ostream& os, const SquareSet& squareset);
    friend SquareSet operator|(const SquareSet& lhs, const SquareSet& rhs);
};