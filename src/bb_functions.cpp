#include "bb_functions.hpp"
#include "types.hpp"
#include "constants.hpp"

void set_bit(Bitboard& bitboard, Square square){
    bitboard |= (1ull << static_cast<int>(square));
}

Bitboard shift_north(Bitboard b){
    return b << 8;
}

Bitboard shift_south(Bitboard b){
    return b >> 8;
}

Bitboard shift_west(Bitboard b){
    return (b >> 1) & NOT_H_FILE;
}

Bitboard shift_east(Bitboard b){
    return (b << 1) & NOT_A_FILE;
}

Bitboard shift_northeast(Bitboard b) {
    return (b << 9) & NOT_A_FILE;
}

Bitboard shift_northwest(Bitboard b) {
    return (b << 7) & NOT_H_FILE;
}

Bitboard shift_southeast(Bitboard b) {
    return (b >> 9) & NOT_A_FILE;
}

Bitboard shift_southwest(Bitboard b) {
    return (b >> 7) & NOT_H_FILE;
}

Bitboard shift_north_north_east(Bitboard b) {return (b << 17) & NOT_A_FILE ;}
Bitboard shift_north_east_east(Bitboard b) {return (b << 10) & NOT_AB_FILE;}
Bitboard shift_south_east_east(Bitboard b) {return (b >> 6) & NOT_AB_FILE;}
Bitboard shift_south_south_east(Bitboard b) {return (b >> 15) & NOT_A_FILE ;}
Bitboard shift_north_north_west(Bitboard b) {return (b << 15) & NOT_H_FILE ;}
Bitboard shift_north_west_west(Bitboard b) {return (b << 6) & NOT_GH_FILE;}
Bitboard shift_south_west_west(Bitboard b) {return (b >> 10) & NOT_GH_FILE;}
Bitboard shift_south_south_west(Bitboard b) {return (b >> 17) & NOT_H_FILE ;}