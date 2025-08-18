#include "bb_functions.hpp"
#include "constants.hpp"
#include "Board.hpp"
#include "types.hpp"

Bitboard knight_possible_targets(Bitboard knight){
    return  shift_north_north_east(knight) |
            shift_north_east_east(knight)  |
            shift_south_east_east(knight)  |
            shift_south_south_east(knight) |
            shift_north_north_west(knight) |
            shift_north_west_west(knight)  |
            shift_south_west_west(knight)  |
            shift_south_south_west(knight);
}

Bitboard pseudo_legal_knight_attacks(Board& board, Color color){
    Bitboard knight_mask = board.get_piece_mask(color, PieceType::KNIGHT);
    return knight_possible_targets(knight_mask);
}