#pragma once
#include "../MoveList.hpp"
#include "../Move.hpp"
#include "../Board.hpp"

MoveList generate_pseudo_pawn_quiet(const Board& board, Color side);
MoveList generate_pseudo_pawn_captures(const Board& board, Color side);
MoveList generate_pseudo_pawn_moves(const Board& board, Color side);