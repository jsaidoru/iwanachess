#include "attacksgen/pawn_attacks.hpp"
#include "Move.hpp"
#include "MoveList.hpp"
#include <vector>
#include <iostream>
#include <chrono>

int rank_of(Square square){
    return static_cast<int>(square) / 8;
}
MoveList generate_pseudo_pawn_quiet(const Board& board, Color side){

    Bitboard pawns = board.get_piece_mask(side, PieceType::PAWN);
    Bitboard empty = ~board.get_occupied_mask();

    MoveList moves;
    for (Square sq : SquareSet(pawns)){
            SquareSet single_pushes = SquareSet(pseudo_single_push_targets(sq, side));
            SquareSet double_pushes = SquareSet(pseudo_double_push_targets(sq, side, empty));

            for (Square to : single_pushes) {
                bool promotion_rank =
                    (side == Color::WHITE && rank_of(to) == 8) ||
                    (side == Color::BLACK && rank_of(to) == 1);

                if (promotion_rank){
                    for (PieceType promo : {PieceType::KNIGHT, PieceType::BISHOP, PieceType::ROOK, PieceType::QUEEN}){
                        moves.add_move(Move(sq, to, promo));
                    }
                }
                else {
                    moves.add_move(Move(sq, to, PieceType::PT_NONE));
                }
            }

            if (double_pushes.size() > 0){
                for (Square to : double_pushes){
                    moves.add_move(Move(sq, to, PieceType::PT_NONE));
                }
            }
    }

    return moves;
}

MoveList generate_pseudo_pawn_captures(const Board& board, Color side){
    MoveList moves;
    Bitboard pawns = board.get_piece_mask(side, PieceType::PAWN);
    Color enemy_color = ~side;
    Bitboard enemy = board.get_occupied_co(enemy_color);

    for (Square sq : SquareSet(pawns)){
        SquareSet captures = SquareSet(pawn_pseudo_legal_captures(sq, side, enemy));
        Square ep_square = board.get_ep_square();
        for (Square to : captures){
            PieceType captured_piece = board.piece_type_at(to);
            moves.add_move(Move(sq, to, captured_piece));
        }

        if (!(ep_square == Square::NO_SQ)){
        moves.add_move(Move(sq, ep_square, PieceType::PAWN));
        }
    }
    return moves;
}

MoveList generate_pseudo_pawn_moves(const Board& board, Color side){
    return generate_pseudo_pawn_quiet(board, side) + generate_pseudo_pawn_captures(board, side);
}

// int main(){
//     Board b("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

//     Bitboard pawns = b.get_piece_mask(Color::WHITE, PieceType::PAWN);
//     Bitboard empty = ~b.get_occupied_mask();

//     auto start = std::chrono::high_resolution_clock::now();

//     for (int i = 0; i < 100000; ++i){
//         std::vector<Move>pawn_moves = generate_pseudo_pawn_quiet(pawns, empty, Color::WHITE);
//     }

//     auto end = std::chrono::high_resolution_clock::now();
//     auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start);

//     std::cout << "Time taken for 100k calls: " << duration.count() << " ns" << "\n";
// }