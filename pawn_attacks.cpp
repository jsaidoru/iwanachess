#include "bb_functions.hpp"
#include "constants.hpp"
#include "Board.hpp"
#include "types.hpp"
#include "SquareSet.hpp"
#include <iostream>
#include <chrono>

Bitboard pseudo_single_push_targets(const Board& board, Color color) {
    Bitboard pawns = board.get_piece_mask(color, PieceType::PAWN);
    Bitboard empty = ~board.get_occupied_mask();

    if (color == Color::WHITE) {
        return shift_north(pawns) & empty;
    } else {
        return shift_south(pawns) & empty;
    }
}

Bitboard pseudo_double_push_targets(const Board& board, Color color) {
    Bitboard single_pushes = pseudo_single_push_targets(board, color);
    Bitboard empty = ~board.get_occupied_mask();

    if (color == Color::WHITE) {
        return shift_north(single_pushes) & empty & BB_RANK_4;
    } else {
        return shift_south(single_pushes) & empty & BB_RANK_5;
    }
}

Bitboard pawn_pseudo_pushes(const Board& board, Color color) {
    return pseudo_single_push_targets(board, color) |  
           pseudo_double_push_targets(board, color);
;
}

Bitboard pawn_pseudo_legal_attacks(const Board& board, Color color) {
    Bitboard pawns = board.get_piece_mask(color, PieceType::PAWN);
    Bitboard attacks;

    if (color == Color::WHITE) {
        attacks = shift_northeast(pawns) | shift_northwest(pawns);
    } else {
        attacks = shift_southeast(pawns) | shift_southwest(pawns);
    }

    return attacks;
}

Bitboard pawn_pseudo_legal_captures(const Board& board, Color color){
    Bitboard enemy = board.get_occupied_co(color == Color::WHITE ? Color::BLACK : Color::WHITE);
    return pawn_pseudo_legal_attacks(board, color) & enemy;
}

Bitboard pawn_pseudo_legal_ep(const Board& board, Color color){
    Square ep_square = board.get_ep_square();
    Bitboard bb_ep = 1ull << static_cast<Bitboard>(ep_square);
    if (ep_square == Square::NO_SQ){
        return 0ull;
    }
    Bitboard pawns = board.get_piece_mask(color, PieceType::PAWN);
    if (color == Color::WHITE){
        Bitboard left_captures = shift_northwest(pawns) & bb_ep;
        Bitboard right_captures = shift_northeast(pawns) & bb_ep;
        return left_captures | right_captures;
    }
    else{
        Bitboard left_captures = shift_southwest(pawns) & bb_ep;
        Bitboard right_captures = shift_southeast(pawns) & bb_ep;
        return left_captures | right_captures;
    }
}

Bitboard generate_pseudo_pawn_pattern(const Board& board, Color color){
    return pawn_pseudo_pushes(board, color) | 
           pawn_pseudo_legal_captures(board, color) | 
           pawn_pseudo_legal_ep(board, color);
}