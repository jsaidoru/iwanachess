#include <iostream>
#include <cstdint>
#include <array>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>
#include <bit>
#include "Board.hpp"
#include "types.hpp"
#include "bb_functions.hpp"
#include "./attacksgen/pawn_attacks.hpp"
#include "./attacksgen/knight_attacks.hpp"
#include "./attacksgen/sliding_piece_att.hpp"
#include "./attacksgen/king_attacks.hpp"

#define PAWNS(c)     bitboards[cast(c)][cast(PieceType::PAWN)]
#define KNIGHTS(c)   bitboards[cast(c)][cast(PieceType::KNIGHT)]
#define BISHOPS(c)   bitboards[cast(c)][cast(PieceType::BISHOP)]
#define ROOKS(c)     bitboards[cast(c)][cast(PieceType::ROOK)]
#define QUEENS(c)    bitboards[cast(c)][cast(PieceType::QUEEN)]
#define KINGS(c)     bitboards[cast(c)][cast(PieceType::KING)]

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
    static_assert(std::is_enum<E>::value, "cast<E> requires E to be an enum type");
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

int Board::get_castling_rights() const{
    return castling_rights;
}

void Board::remove_piece_at(Square square, Color color, PieceType pt){
    clear_bit(bitboards[cast(color)][cast(pt)], square);
    clear_bit(occupied_co[cast(color)], square);
    clear_bit(occupied, square);
}

void Board::set_piece_at(Square square, Color color, PieceType pt){
    set_bit(bitboards[cast(color)][cast(pt)], square);
    set_bit(occupied_co[cast(color)], square);
    set_bit(occupied, square);
}

bool Board::is_castling(const Move& move) {
    Square from = move.from();
    Square to = move.to();
    Bitboard kings = KINGS(Color::WHITE) | KINGS(Color::BLACK);

    if (kings & (1ull << cast(from))){
        int diff = cast(to) - cast(from);
        return diff == 2 || diff == -2;
    }

    return false;
}

Bitboard Board::attackers_mask(Color color, Square square){
    Bitboard attackers = 0ull;
    attackers |= (pawn_pseudo_legal_attacks(square, ~color) & PAWNS(~color));

    attackers |= (pseudo_legal_knight_attacks(square, color) & PAWNS(~color));
    attackers |= generate_pseudo_bishop_attacks(cast(square), occupied) 
        & BISHOPS(color) | QUEENS(color);
    attackers |= generate_pseudo_rook_attacks(cast(square), occupied) 
        & (ROOKS(color) | QUEENS(color));

    attackers |= (pseudo_legal_king_attacks(square, color) & KINGS(~color));

    return attackers;
}

void Board::update_castling_rights(Square from, Square to, PieceType piece, PieceType captured) {
    // if king moves, lose both rights
    if (piece == PieceType::KING) {
        if (side_to_move == Color::WHITE) castling_rights &= ~(1 | 2); // white k+q
        else castling_rights &= ~(4 | 8); // black k+q
    }

    // if rook moves, lose its side
    if (piece == PieceType::ROOK) {
        if (from == Square::H1) castling_rights &= ~1;
        if (from == Square::A1) castling_rights &= ~2;
        if (from == Square::H8) castling_rights &= ~4;
        if (from == Square::A8) castling_rights &= ~8;
    }

    // if rook is captured on original square, lose rights too
    if (captured == PieceType::ROOK) {
        if (to == Square::H1) castling_rights &= ~1;
        if (to == Square::A1) castling_rights &= ~2;
        if (to == Square::H8) castling_rights &= ~4;
        if (to == Square::A8) castling_rights &= ~8;
    }
}

bool Board::is_capture(const Move& move){
    return piece_type_at(move.to()) != PieceType::PT_NONE;
}

int file_of(Square sq){
    return cast(sq) % 8;
}
int rank_of(Square sq){
    return cast(sq) / 8;
}

bool Board::is_en_passant(const Move& move, Color us, Square en_passant_square) {
    // must be a pawn move
    if (move.promotion_type() != PieceType::PT_NONE) return false;
    if (piece_type_at(move.from()) != PieceType::PAWN) return false;

    // en passant square must match the destination
    return move.to() == en_passant_square;
}

int Board::push(const Move& move) {
    state_stack.push_back({
        castling_rights,
        side_to_move,
        en_passant_square,
        halfmove_clock,
        fullmove_number,
        is_capture(move) ? piece_type_at(move.to()) : PieceType::PT_NONE
    });

    Square from = move.from();
    Square to = move.to();
    Color us = side_to_move;
    Color them = ~us;
    PieceType piece = piece_type_at(from);
    PieceType captured = piece_type_at(to);

    // en passant capture
    if (piece == PieceType::PAWN && to == en_passant_square) {
        Square cap_sq = static_cast<Square>((us == Color::WHITE) ? static_cast<int>(to) - 8 : static_cast<int>(to) + 8);
        remove_piece_at(cap_sq, them, PieceType::PAWN);
        captured = PieceType::PAWN;
    }

    // move piece
    remove_piece_at(from, us, piece);
    if (captured != PieceType::PT_NONE)
        remove_piece_at(to, them, captured);
    set_piece_at(to, us, piece);

    // promotion
    if (move.promotion_type() != PieceType::PT_NONE) {
        set_piece_at(move.to(), us, move.promotion_type());
    } else {
        set_piece_at(move.to(), us, piece);
    }

    // castling rook move
    if (is_castling(move)) {
        if (to == Square::G1) { remove_piece_at(Square::H1, Color::WHITE, PieceType::ROOK); set_piece_at(Square::F1, Color::WHITE, PieceType::ROOK); }
        if (to == Square::C1) { remove_piece_at(Square::A1, Color::WHITE, PieceType::ROOK); set_piece_at(Square::D1, Color::WHITE, PieceType::ROOK); }
        if (to == Square::G8) { remove_piece_at(Square::H8, Color::BLACK, PieceType::ROOK); set_piece_at(Square::F8, Color::BLACK, PieceType::ROOK); }
        if (to == Square::C8) { remove_piece_at(Square::A8, Color::BLACK, PieceType::ROOK); set_piece_at(Square::D8, Color::BLACK, PieceType::ROOK); }
    }

    // update castling rights (king or rook moves/captures)
    update_castling_rights(from, to, piece, captured);

    // update en passant target
    if (piece == PieceType::PAWN && abs(cast(to) - cast(from)) == 16)
        en_passant_square = static_cast<Square>((cast(from) + cast(to)) / 2);
    else
        en_passant_square = Square::NO_SQ;

    // move clocks
    if (piece == PieceType::PAWN || captured != PieceType::PT_NONE) halfmove_clock = 0;
    else halfmove_clock++;
    if (us == Color::BLACK) fullmove_number++;

    // flip side
    side_to_move = them;

    // check legality (is our king in check)
    Square king_sq = static_cast<Square>(lsb(KINGS(us)));
    if (attackers_mask(them, king_sq)) {
        return -1;
    }

    // check legality (capturing friendly piece)
    if ((1ull << cast(move.to())) & occupied_co[cast(us)]) {
        return -1;
    }

    return 0;
}

int Board::pop() {
    if (state_stack.empty()) return 0;

    BoardState prev = state_stack.back();
    state_stack.pop_back();

    Move move = move_stack.back();
    move_stack.pop_back();

    // restore state
    castling_rights   = prev.castling_rights;
    side_to_move      = prev.side_to_move;
    en_passant_square = prev.en_passant_square;
    halfmove_clock    = prev.halfmove_clock;
    fullmove_number   = prev.fullmove_number;

    Color us = side_to_move;
    Color them = Color(~us);

    // undo castling first (king + rook)
    if (is_castling(move)) {
        if (file_of(move.to()) == 7) { // kingside
            // King
            remove_piece_at(move.to(), us, PieceType::KING);
            set_piece_at(move.from(), us, PieceType::KING);

            // rook
            remove_piece_at(convert_square_from_coords(6, rank_of(move.from())), us, PieceType::ROOK);
            set_piece_at(convert_square_from_coords(8, rank_of(move.from())), us, PieceType::ROOK);
        } else { // queenside
            remove_piece_at(move.to(), us, PieceType::KING);
            set_piece_at(move.from(), us, PieceType::KING);

            remove_piece_at(convert_square_from_coords(4, rank_of(move.from())), us, PieceType::ROOK);
            set_piece_at(convert_square_from_coords(1, rank_of(move.from())), us, PieceType::ROOK);
        }
    }
    else {
        // normal / promotion
        PieceType restore = (move.promotion_type() != PieceType::PT_NONE) 
            ? PieceType::PAWN : prev.moved;
        remove_piece_at(move.to(), us, 
        move.promotion_type() != PieceType::PT_NONE ? move.promotion_type() : prev.moved);

    set_piece_at(move.from(), us, restore);
    }

    // restore captured
    if (prev.captured != PieceType::PT_NONE) {
        if (is_en_passant(move, us, en_passant_square)) {
            Square cap_sq = convert_square_from_coords(file_of(move.to()), rank_of(move.from()));
            set_piece_at(cap_sq, them, PieceType::PAWN);
        } else {
            set_piece_at(move.to(), them, prev.captured);
        }
    }

    return 0;
}


std::ostream& operator<<(std::ostream& os, const Board& board) {
    os << board.to_ascii();
    return os;
}