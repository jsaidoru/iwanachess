#pragma once
#include <iostream>
#include <cstdint>
#include <array>
#include <string>
#include <sstream>
#include <vector>
#include "types.hpp"
#include "Move.hpp"

struct BoardState {
    int castling_rights;
    Color side_to_move;
    Square en_passant_square;
    int halfmove_clock;
    int fullmove_number;
    PieceType captured;
    PieceType moved;
};

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

    std::vector<BoardState> state_stack;
    std::vector<Move> move_stack;

    void reset_bitboard();

    void remove_piece_at(Square square, Color color, PieceType pt);

    void set_piece_at(Square square, Color color, PieceType pt);

    Bitboard attackers_mask(Color color, Square square);
    
public:
    Board(const std::string& fen);
    void set_bb_from_fen();

    std::string to_ascii() const;

    Bitboard get_piece_mask(Color color, PieceType piece_type) const;

    Bitboard get_occupied_co(Color color) const;

    Bitboard get_occupied_mask() const;

    Square get_ep_square() const;

    void get_all_bitboard();

    inline Color get_side_to_move() const {return side_to_move;}

    PieceType piece_type_at(Square square) const;

    int get_castling_rights() const;

    void update_castling_rights(Square from, Square to, PieceType piece, PieceType captured);

    bool is_capture(const Move& move);

    bool is_en_passant(const Move& move, Color us, Square en_passant_square);

    int push(const Move& move);

    int pop();

    bool is_castling(const Move& move);

    friend std::ostream& operator<<(std::ostream& os, const Board& board);
};