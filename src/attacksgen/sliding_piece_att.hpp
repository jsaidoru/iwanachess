#pragma once
#include "../types.hpp"

Bitboard generate_pseudo_rook_attacks(int sq, Bitboard occupancy);
Bitboard generate_pseudo_bishop_attacks(int sq, Bitboard occupancy);
Bitboard generate_pseudo_queen_attacks(int sq, Bitboard occupancy);