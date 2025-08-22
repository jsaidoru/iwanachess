#include "bb_functions.hpp"
#include "constants.hpp"
#include "Board.hpp"
#include "types.hpp"
#include "SquareSet.hpp"
#include <iostream>
#include <chrono>

Bitboard pseudo_single_push_targets(Square square, Color color) {
    Bitboard pawn_mask = 1ull << static_cast<int>(square);
    if (color == Color::WHITE){
        return shift_north(pawn_mask);
    }
    else{
        return shift_south(pawn_mask);
    }
}

Bitboard pseudo_double_push_targets(Square square, Color color, Bitboard empty) {
    Bitboard single_pushes = pseudo_single_push_targets(square, color);

    if (color == Color::WHITE) {
        return shift_north(single_pushes) & empty & BB_RANK_4;
    } else {
        return shift_south(single_pushes) & empty & BB_RANK_5;
    }
}

Bitboard pawn_pseudo_pushes(Square square, Color color, Bitboard empty) {
    return pseudo_single_push_targets(square, color) |  
           pseudo_double_push_targets(square, color, empty);
;
}

Bitboard pawn_pseudo_legal_attacks(Square square, Color color) {
    Bitboard pawn_mask = 1ull << static_cast<int>(square);
    Bitboard attacks;

    if (color == Color::WHITE) {
        attacks = shift_northeast(pawn_mask) | shift_northwest(pawn_mask);
    } else {
        attacks = shift_southeast(pawn_mask) | shift_southwest(pawn_mask);
    }

    return attacks;
}

Bitboard pawn_pseudo_legal_captures(Square square, Color color, Bitboard enemy){
    return pawn_pseudo_legal_attacks(square, color) & enemy;
}

Bitboard pawn_pseudo_legal_ep(Square square, Color color, Square ep_square){
    Bitboard bb_ep = 1ull << static_cast<Bitboard>(ep_square);
    if (ep_square == Square::NO_SQ){
        return 0ull;
    }

    Bitboard pawn_mask = 1ull << static_cast<int>(square);
    if (color == Color::WHITE){
        Bitboard left_captures = shift_northwest(pawn_mask) & bb_ep;
        Bitboard right_captures = shift_northeast(pawn_mask) & bb_ep;
        return left_captures | right_captures;
    }
    else{
        Bitboard left_captures = shift_southwest(pawn_mask) & bb_ep;
        Bitboard right_captures = shift_southeast(pawn_mask) & bb_ep;
        return left_captures | right_captures;
    }
}

Bitboard generate_pseudo_pawn_pattern(Square square, Color color, Bitboard empty, Bitboard enemy, Square ep_square){
    return pawn_pseudo_pushes(square, color, empty) | 
           pawn_pseudo_legal_captures(square, color, enemy) | 
           pawn_pseudo_legal_ep(square, color, ep_square);
}