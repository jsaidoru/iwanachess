#include "../MoveList.hpp"
#include "../Board.hpp"
#include "generate_bishop_moves.hpp"
#include "generate_rook_moves.hpp"
#include "generate_queen_moves.hpp"

MoveList generate_pseudo_queen_moves(const Board& board, Color side){
    
    return generate_pseudo_bishop_moves(board, side) + generate_pseudo_rook_moves(board, side);
}