#include "../types.hpp"
#include "init_sliding_attacks.hpp"
#include "init_sliding_attacks.cpp"
#include "../bb_functions.hpp"
#include "sliding_piece_att.hpp"

Bitboard generate_pseudo_rook_attacks(int sq, Bitboard occupancy) {
    Bitboard blockers   = occupancy & rook_mask[sq];
    uint64_t magic_index = (blockers * rook_magic[sq]) >> (64 - __builtin_popcountll(sq));
    return rook_attacks[sq][magic_index];
}

Bitboard generate_pseudo_bishop_attacks(int sq, Bitboard occupancy) {
    Bitboard blockers   = occupancy & bishop_mask[sq];
    uint64_t magic_index = (blockers * bishop_magic[sq]) >> (64 - __builtin_popcountll(sq));
    return bishop_attacks[sq][magic_index];
}

Bitboard generate_pseudo_queen_attacks(int sq, Bitboard occupancy){
    return generate_pseudo_rook_attacks(sq, occupancy) | generate_pseudo_bishop_attacks(sq, occupancy);
}