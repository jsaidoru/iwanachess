#pragma once
#include "types.hpp"
#include "Board.hpp"
#include "SquareSet.hpp"

Bitboard pseudo_single_push_targets(const Board& board, Color color);
Bitboard pseudo_double_push_targets(const Board& board, Color color);
Bitboard pawn_pseudo_pushes(const Board& board, Color color);
Bitboard pawn_pseudo_legal_attacks(const Board& board, Color color);
Bitboard pawn_pseudo_legal_captures(const Board& board, Color color);
Bitboard pawn_pseudo_legal_ep(const Board& board, Color color);
Bitboard generate_pseudo_pawn_pattern(const Board& board, Color color);