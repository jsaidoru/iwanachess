#pragma once
#include "types.hpp"

inline constexpr Bitboard BB_RANK_1 = 0xffull << (8*0);
inline constexpr Bitboard BB_RANK_2 = 0xffull << (8*1);
inline constexpr Bitboard BB_RANK_3 = 0xffull << (8*2);
inline constexpr Bitboard BB_RANK_4 = 0xffull << (8*3);
inline constexpr Bitboard BB_RANK_5 = 0xffull << (8*4);
inline constexpr Bitboard BB_RANK_6 = 0xffull << (8*5);
inline constexpr Bitboard BB_RANK_7 = 0xffull << (8*6);
inline constexpr Bitboard BB_RANK_8 = 0xffull << (8*7);

inline constexpr Bitboard NOT_A_FILE = 0xfefefefefefefefeull;
inline constexpr Bitboard NOT_AB_FILE = 0xfcfcfcfcfcfcfcfcull;
inline constexpr Bitboard NOT_ABF_FILE = 0xdcdcdcdcdcdcdcdcull;
inline constexpr Bitboard NOT_AF_FILE = 0xdedededededededeull;
inline constexpr Bitboard NOT_FGH_FILE = 0x1f1f1f1f1f1f1f1full;
inline constexpr Bitboard NOT_GH_FILE = 0x3f3f3f3f3f3f3f3full;
inline constexpr Bitboard NOT_H_FILE = 0x7f7f7f7f7f7f7f7full;
inline constexpr Bitboard NOT_HF_FILE = 0x5f5f5f5f5f5f5f5full;