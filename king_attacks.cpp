#include "bb_functions.hpp"
#include "constants.hpp"
#include "Board.hpp"
#include "types.hpp"

Bitboard king_possible_targets(Bitboard king){
    return  shift_north(king)     |
            shift_south(king)     |
            shift_east(king)      |
            shift_west(king)      |
            shift_northeast(king) |
            shift_northwest(king) |
            shift_southeast(king) |
            shift_southwest(king);
}

Bitboard pseudo_legal_king_attacks(Board& board, Color color){
    Bitboard king_mask = board.get_piece_mask(color, PieceType::KING);
    return king_possible_targets(king_mask);
}