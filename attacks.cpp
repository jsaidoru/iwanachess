#include <attacks.hpp>
#include <bb_functions.hpp>
#include <constants.hpp>
#include <Board.hpp>
#include <types.hpp>
#include <SquareSet.hpp>

SquareSet single_push_targets(const Board& board, Color color) {
    Bitboard pawns = board.get_piece_mask(color, PieceType::PAWN);
    Bitboard empty = ~board.get_occupied_mask();

    if (color == Color::WHITE) {
        return SquareSet(shift_north(pawns) & empty);
    } else {
        return SquareSet(shift_south(pawns) & empty);
    }
}

SquareSet double_push_targets(const Board& board, Color color) {
    Bitboard single_pushes = single_push_targets(board, color).get_mask();
    Bitboard empty = ~board.get_occupied_mask();

    if (color == Color::WHITE) {
        return SquareSet(shift_north(single_pushes) & empty & BB_RANK_4);
    } else {
        return SquareSet(shift_south(single_pushes) & empty & BB_RANK_5);
    }
}

SquareSet pawn_pushes(const Board& board, Color color) {
    return SquareSet(
        single_push_targets(board, color).get_mask() |
        double_push_targets(board, color).get_mask()
    );
}
