#pragma once
int lsb(Bitboard bb);
Bitboard set_occupancy(int index, int bits, Bitboard mask);
std::vector<Bitboard> generate_all_blockers(Bitboard mask);
Bitboard compute_rook_attack(int square, Bitboard blockers);
Bitboard compute_bishop_attack(int square, Bitboard blockers);
Bitboard find_magic(int square, Bitboard mask, AttackFunc compute_attack);
void init_rook_attacks(int sq);
void init_bishop_attacks(int sq);