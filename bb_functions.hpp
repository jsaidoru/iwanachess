#pragma once
#include "types.hpp"
#include "constants.hpp"

Bitboard shift_north(Bitboard& bitboard){
    return bitboard << 8;
}

Bitboard shift_south(Bitboard& bitboard){
    return bitboard >> 8;
}