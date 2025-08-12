#pragma once
#include <iostream>
#include <cstdint>
#include <array>
#include <string>
#include <sstream>
#include <vector>

using Bitboard = uint64_t;
using PieceType = int;
using Color = int;

enum class Col { BLACK, WHITE, COLOR_NB };
enum class PType { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, PIECE_TYPE_NB };

constexpr int COLOR_NB = static_cast<int>(Col::COLOR_NB);
constexpr int PIECE_TYPE_NB = static_cast<int>(PType::PIECE_TYPE_NB);

constexpr Color WHITE = 1;
constexpr Color BLACK = 0;

constexpr PieceType PAWN = 0;
constexpr PieceType KNIGHT = 1;
constexpr PieceType BISHOP = 2;
constexpr PieceType ROOK = 3;
constexpr PieceType QUEEN = 4;
constexpr PieceType KING = 5;

class Board {
private:
    std::array<std::array<Bitboard, PIECE_TYPE_NB>, COLOR_NB> bitboards{};
    std::array<Bitboard, COLOR_NB> occupied_co{};
    std::array<PType, PIECE_TYPE_NB> piece_type{};
    std::array<Color, COLOR_NB> color{};
    Bitboard occupied = 0ull;

    int castling_rights = 0;
    Color side_to_move = 0;
    int en_passant_square = -1;
    int halfmove_clock = 0;
    int fullmove_number = 0;
    std::string fen;

    void set_bit(Bitboard &bb, int square) {
        bb |= (1ULL << square);
    }

public:
    Board();
    void set_bb_from_fen();

    std::string to_ascii() const;

    friend std::ostream& operator<<(std::ostream& os, const Board& board) {
        os << board.to_ascii();
        return os;
    }
};