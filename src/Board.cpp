#include <iostream>
#include <cstdint>
#include <array>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>
#include "Board.hpp"
#include "types.hpp"
#include "bb_functions.hpp"

using Bitboard = uint64_t;

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

Square convert_square_from_coords(char file, char rank) {
    return static_cast<Square>((rank - '1') * 8 + (file - 'a'));
}

template<typename E>
constexpr auto cast(E e) noexcept {
    return static_cast<std::underlying_type_t<E>>(e);
}

Board::Board(const std::string& fen){
    Board::fen = fen;
    set_bb_from_fen();
}

void Board::reset_bitboard(){
    for (int color = 0; color < 2; color++) {
        for (int piece = 0; piece < 6; piece++) {
            bitboards[color][piece] = 0ull;
        }
        occupied_co[color] = 0ull;
    }
    occupied = 0ull;
    castling_rights = 0;
}

void Board::set_bb_from_fen(){
    reset_bitboard();

    std::vector<std::string> fen_parts = split(fen, ' '); 
    // format: piece placement, side to move, castling rights, en passant square, halfmove clock, fullmove number
    int square = 56; // a8 in LERF mapping

    std::string pieces = fen_parts[0];
    for (char c : pieces){
        if (c == '/'){
            square -= 16;
        }
        else if (isdigit(c)){
            square += c - '0';
        }
        else{
            Color color = isupper(c) ? Color::WHITE : Color::BLACK;
            PieceType pt;
            switch (std::tolower(c)){
                case 'p': pt = PieceType::PAWN;   break;
                case 'n': pt = PieceType::KNIGHT; break;
                case 'b': pt = PieceType::BISHOP; break;
                case 'r': pt = PieceType::ROOK;   break;
                case 'q': pt = PieceType::QUEEN;  break;
                case 'k': pt = PieceType::KING;   break;
                default: continue;
            }

            set_bit(bitboards[cast(color)][cast(pt)], static_cast<Square>(square));
            occupied_co[cast(color)] |= (1ull << square);
            occupied |= (1ull << square);
            square++;
        }
    }

    std::string side = fen_parts[1];
    side_to_move = side == "w" ? Color::WHITE : Color::BLACK;

    std::string castling = fen_parts[2];
    for (char c : castling){
        switch (c){
            case 'K': castling_rights |= 1; break;
            case 'Q': castling_rights |= 2; break;
            case 'k': castling_rights |= 4; break;
            case 'q': castling_rights |= 8; break;
        }
    }

    std::string enpassant = fen_parts[3];
    if (enpassant == "-"){
        en_passant_square = Square::NO_SQ;
    }
    else{
        en_passant_square = convert_square_from_coords(enpassant[0], enpassant[1]);
    }

    std::string halfmove = fen_parts[4];
    halfmove_clock = std::stoi(halfmove);

    std::string fullmove = fen_parts[5];
    fullmove_number = std::stoi(fullmove);

}

std::string Board::to_ascii() const {
    std::string board;
    std::string position = split(fen, ' ')[0];

    for (char c : position) {
        if (c == '/') {
            board.append("\n");
        }
        else if (isdigit(c)) {
            for (int i = 0; i < c - '0'; ++i) {
                board += ". ";
            }
        }
        else {
            board += c;
            board += " ";
        }
    }

    return board;
}

Bitboard Board::get_piece_mask(Color color, PieceType piece_type) const{
    return bitboards[cast(color)][cast(piece_type)];
}

Bitboard Board::get_occupied_co(Color color) const{
    return occupied_co[cast(color)];
}

Bitboard Board::get_occupied_mask() const{
    return occupied;
}

void Board::get_all_bitboard(){
    for (size_t color = 0; color < COLOR_NB; ++color) {
        for (size_t piece = 0; piece < PIECE_TYPE_NB; ++piece) {
            std::cout << "Color " << color
                    << ", Piece " << piece
                    << ": " << bitboards[color][piece] << "\n";
        }
    }
}

Square Board::get_ep_square() const{
    return en_passant_square;
}

PieceType Board::piece_type_at(Square square) const{
    Bitboard mask = 1ull << static_cast<int>(square);
    Bitboard pawns = get_piece_mask(Color::WHITE, PieceType::PAWN) | get_piece_mask(Color::BLACK, PieceType::PAWN);
    Bitboard knights = get_piece_mask(Color::WHITE, PieceType::KNIGHT) | get_piece_mask(Color::BLACK, PieceType::KNIGHT);
    Bitboard bishops = get_piece_mask(Color::WHITE, PieceType::BISHOP) | get_piece_mask(Color::BLACK, PieceType::BISHOP);
    Bitboard rooks = get_piece_mask(Color::WHITE, PieceType::ROOK) | get_piece_mask(Color::BLACK, PieceType::ROOK);
    Bitboard queens = get_piece_mask(Color::WHITE, PieceType::QUEEN) | get_piece_mask(Color::BLACK, PieceType::QUEEN);
    Bitboard king = get_piece_mask(Color::WHITE, PieceType::KING) | get_piece_mask(Color::BLACK, PieceType::KING);

    if (!(occupied & mask)){
        return PieceType::PT_NONE;
    }
    else if (pawns & mask){
        return PieceType::PAWN;
    }
    else if (knights & mask){
        return PieceType::KNIGHT;
    }
    else if (bishops & mask){
        return PieceType::BISHOP;
    }
    else if (rooks & mask){
        return PieceType::ROOK;
    }
    else if (queens & mask){
        return PieceType::QUEEN;
    }
    else{
        return PieceType::KING;
    }
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
    os << board.to_ascii();
    return os;
}