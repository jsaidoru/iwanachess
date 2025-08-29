#include "generate_pawn_moves.hpp"
#include "generate_knight_moves.hpp"
#include "generate_bishop_moves.hpp"
#include "generate_rook_moves.hpp"
#include "generate_queen_moves.hpp"
#include "generate_king_moves.hpp"
#include "../MoveList.hpp"
#include "generate_all_moves.hpp"
#include "../Board.hpp"
#include "../types.hpp"

MoveList generate_all_pseudo_moves(const Board& board){
    Color us = board.get_side_to_move();
    return  generate_pseudo_pawn_moves(board, us) +
            generate_pseudo_knight_moves(board, us) +
            generate_pseudo_bishop_moves(board, us) +
            generate_pseudo_rook_moves(board, us) +
            generate_pseudo_queen_moves(board, us) +
            generate_pseudo_king_moves(board, us);
}