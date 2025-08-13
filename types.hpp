#pragma once
#include <cstdint>
#include <array>

using Bitboard = uint64_t;
using Square = int;

enum class Color { BLACK, WHITE, COLOR_NB };
enum class PieceType { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, PIECE_TYPE_NB };

Square A1 = 0;
Square B1 = 1;
Square C1 = 2;
Square D1 = 3;
Square E1 = 4;
Square F1 = 5;
Square G1 = 6;
Square H1 = 7;
Square A2 = 8;
Square B2 = 9;
Square C2 = 10;
Square D2 = 11;
Square E2 = 12;
Square F2 = 13;
Square G2 = 14;
Square H2 = 15;
Square A3 = 16;
Square B3 = 17;
Square C3 = 18;
Square D3 = 19;
Square E3 = 20;
Square F3 = 21;
Square G3 = 22;
Square H3 = 23;
Square A4 = 24;
Square B4 = 25;
Square C4 = 26;
Square D4 = 27;
Square E4 = 28;
Square F4 = 29;
Square G4 = 30;
Square H4 = 31;
Square A5 = 32;
Square B5 = 33;
Square C5 = 34;
Square D5 = 35;
Square E5 = 36;
Square F5 = 37;
Square G5 = 38;
Square H5 = 39;
Square A6 = 40;
Square B6 = 41;
Square C6 = 42;
Square D6 = 43;
Square E6 = 44;
Square F6 = 45;
Square G6 = 46;
Square H6 = 47;
Square A7 = 48;
Square B7 = 49;
Square C7 = 50;
Square D7 = 51;
Square E7 = 52;
Square F7 = 53;
Square G7 = 54;
Square H7 = 55;
Square A8 = 56;
Square B8 = 57;
Square C8 = 58;
Square D8 = 59;
Square E8 = 60;
Square F8 = 61;
Square G8 = 62;
Square H8 = 63;

constexpr int COLOR_NB = 2;
constexpr int PIECE_TYPE_NB = 6;