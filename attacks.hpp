#pragma once
#include <types.hpp>
#include <Board.hpp>
#include <attacks.cpp>

SquareSet white_single_push_targets(const Board& board);
SquareSet white_double_push_targets(const Board& board);
SquareSet black_single_push_targets(const Board& board);
SquareSet black_double_push_targets(const Board& board);