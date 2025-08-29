#include "attacksgen/king_attacks.hpp"
#include "../Move.hpp"
#include "../MoveList.hpp"
#include "../Board.hpp"
#include "../types.hpp"
#include "../SquareSet.hpp"
#include "generate_king_moves.hpp"

enum castling_rights : int{
    WHITE_KINGSIDE = 1 >> 0,
    WHITE_QUEENSIDE = 1 >> 1,
    BLACK_KINGSIDE = 1 >> 2,
    BLACK_QUEENSIDE = 1 >> 3
};

MoveList generate_pseudo_king_moves(const Board& board, Color side){
    MoveList moves;
    Bitboard kings = board.get_piece_mask(side, PieceType::KING);
    for (Square sq: SquareSet(kings)){
        Bitboard attacks = pseudo_legal_king_attacks(sq, side);
        for (Square to : SquareSet(attacks)){
            PieceType captured_piece = board.piece_type_at(to);
            moves.add_move(Move(sq, to, captured_piece));
        }
    }

    if (board.get_castling_rights() & WHITE_KINGSIDE && side == Color::WHITE){
        moves.add_move(Move(Square::E1, Square::G1, PieceType::PT_NONE));
    }
    if (board.get_castling_rights() & WHITE_QUEENSIDE && side == Color::WHITE){
        moves.add_move(Move(Square::E1, Square::C1, PieceType::PT_NONE));
    }
    if (board.get_castling_rights() & BLACK_KINGSIDE && side == Color::BLACK){
        moves.add_move(Move(Square::E8, Square::G8, PieceType::PT_NONE));
    }
    if (board.get_castling_rights() & BLACK_KINGSIDE && side == Color::BLACK){
        moves.add_move(Move(Square::E8, Square::C8, PieceType::PT_NONE));
    }

    return moves;
}