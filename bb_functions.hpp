#pragma once
#include "types.hpp"
#include "constants.hpp"

void set_bit(Bitboard& bitboard, Square square);

Bitboard shift_north(Bitboard b);

Bitboard shift_south(Bitboard b);

Bitboard shift_west(Bitboard b);

Bitboard shift_east(Bitboard b);

Bitboard shift_northeast(Bitboard b);

Bitboard shift_northwest(Bitboard b);

Bitboard shift_southeast(Bitboard b);

Bitboard shift_southwest(Bitboard b);

Bitboard shift_north_north_east(Bitboard b);
Bitboard shift_north_east_east(Bitboard b);
Bitboard shift_south_east_east(Bitboard b);
Bitboard shift_south_south_east(Bitboard b);
Bitboard shift_north_north_west(Bitboard b);
Bitboard shift_north_west_west(Bitboard b);
Bitboard shift_south_west_west(Bitboard b);
Bitboard shift_south_south_west(Bitboard b);