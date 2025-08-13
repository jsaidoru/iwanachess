#include <iostream>
#include <cstdint>
#include <array>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>
#include "Board.hpp"
#include "types.hpp"

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

void Board::set_bit(Bitboard &bb, int square) {
    bb |= (1ULL << square);
}

Square convert_square_from_coords(char file, char rank) {
    return (rank - '1') * 8 + (file - 'a');
}

constexpr size_t idx(Color c)   { return static_cast<size_t>(c); }
constexpr size_t idx(PieceType p)   { return static_cast<size_t>(p); }

void Board::set_bb_from_fen(){
    std::vector<std::string> fen_parts = split(fen, ' '); 
    // format: piece placement, side to move, castling rights, en passant square, halfmove clock, fullmove number
    int square = 56; // a8 in LERF mapping

    std::string pieces = fen_parts[0];
    for (char c : pieces){
        if (c == '/'){
            square -= 8;
        }
        else if (isdigit(c)){
            square += 'c' - '0';
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

            set_bit(bitboards[idx(color)][idx(pt)], square);
            occupied_co[idx(color)] |= (1ull << square);
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
        en_passant_square = -1;
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
    return bitboards[idx(color)][idx(piece_type)];
}

Bitboard Board::get_occupied_mask() const{
    return occupied;
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
    os << board.to_ascii();
    return os;
}