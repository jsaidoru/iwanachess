#include "../MoveList.hpp"
#include "../Move.hpp"
#include "../types.hpp"
#include "../Board.hpp"
#include "../SquareSet.hpp"
#include "attacksgen/knight_attacks.hpp"
#include "generate_knight_moves.hpp"

MoveList generate_pseudo_knight_moves(const Board& board, Color side){
    MoveList moves;
    Bitboard knights = board.get_piece_mask(side, PieceType::KNIGHT);
    
    for (Square sq : SquareSet(knights)){
        Bitboard attacks = pseudo_legal_knight_attacks(sq, side);
        for (Square to : SquareSet(attacks)){
            PieceType captured_piece = board.piece_type_at(to);
            moves.add_move(Move(sq, to, captured_piece));
        }
    }

    return moves;
}