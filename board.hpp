#pragma once
#include <iostream>
#include <cstdint>
#include <array>
#include <string>
#include <sstream>
#include <vector>
#include "types.hpp"

class Board {
private:
    std::array<std::array<Bitboard, PIECE_TYPE_NB>, COLOR_NB> bitboards{};
    std::array<Bitboard, COLOR_NB> occupied_co{};
    Bitboard occupied = 0ull;

    int castling_rights = 0;
    Color side_to_move = Color::WHITE;
    Square en_passant_square = Square::NO_SQ;
    int halfmove_clock = 0;
    int fullmove_number = 0;
    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    void reset_bitboard();
public:
    Board(const std::string& fen);
    void set_bb_from_fen();

    std::string to_ascii() const;

    Bitboard get_piece_mask(Color color, PieceType piece_type) const;

    Bitboard get_occupied_co(Color color) const;

    Bitboard get_occupied_mask() const;

    Square get_ep_square() const;

    void get_all_bitboard();

    friend std::ostream& operator<<(std::ostream& os, const Board& board);
};