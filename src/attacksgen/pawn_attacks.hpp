#pragma once
#include "types.hpp"
#include "Board.hpp"
#include "SquareSet.hpp"
#include "bb_functions.hpp"

Bitboard pseudo_single_push_targets(Square square, Color color);
Bitboard pseudo_double_push_targets(Square square, Color color, Bitboard empty);
Bitboard pawn_pseudo_pushes(Square square, Color color, Bitboard empty);
Bitboard pawn_pseudo_legal_attacks(Square square, Color color);
Bitboard pawn_pseudo_legal_captures(Square square, Color color, Bitboard enemy);
Bitboard pawn_pseudo_legal_ep(Square square, Color color, Square ep_square);
Bitboard generate_pseudo_pawn_pattern(Square square, Color color, Bitboard empty, Bitboard enemy, Square ep_square);