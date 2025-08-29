#pragma once
Bitboard set_occupancy(int index, int bits, Bitboard mask);
std::vector<Bitboard> generate_all_blockers(Bitboard mask);
Bitboard compute_rook_attack(int square, Bitboard blockers);
Bitboard compute_bishop_attack(int square, Bitboard blockers);
Bitboard find_magic(int square, Bitboard mask, AttackFunc compute_attack);
constexpr auto generate_rook_attacks_for_square(int sq);
constexpr auto init_rook_attacks();
constexpr auto generate_bishop_attacks_for_square(int sq);
constexpr auto init_bishop_attacks();