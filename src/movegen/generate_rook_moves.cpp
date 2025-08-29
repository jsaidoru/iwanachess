#include "attacksgen/sliding_piece_att.hpp"
#include "../Move.hpp"
#include "../MoveList.hpp"
#include "../types.hpp"
#include "../Board.hpp"
#include "../SquareSet.hpp"

MoveList generate_pseudo_rook_moves(const Board& board, Color side){
    MoveList moves;
    Bitboard rooks = board.get_piece_mask(side, PieceType::ROOK);
    Bitboard occupied = board.get_occupied_mask();
    

    for (Square sq : SquareSet(rooks)){
        Bitboard attacks = generate_pseudo_rook_attacks(static_cast<int>(sq), occupied);
        for (Square to : SquareSet(attacks)){
            PieceType captured_piece = board.piece_type_at(to);
            moves.add_move(Move(sq, to, captured_piece));
        }
    }

    return moves;
}