#include "../bb_functions.hpp"
#include "constants.hpp"
#include "../Board.hpp"
#include "../types.hpp"
#include "knight_attacks.hpp"

Bitboard knight_possible_targets(Bitboard knight){
    return  shift_north_north_east(knight) |
            shift_north_east_east(knight)  |
            shift_south_east_east(knight)  |
            shift_south_south_east(knight) |
            shift_north_north_west(knight) |
            shift_north_west_west(knight)  |
            shift_south_west_west(knight)  |
            shift_south_south_west(knight);
}

Bitboard pseudo_legal_knight_attacks(Square square, Color color){
    Bitboard knight_mask = 1ull << static_cast<int>(square);
    return knight_possible_targets(knight_mask);
}