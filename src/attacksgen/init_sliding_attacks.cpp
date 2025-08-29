#include "../types.hpp"
#include "init_sliding_attacks.hpp"
#include "../bb_functions.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <cstdio>
#include <chrono>

std::array<Bitboard, 64>rook_mask = {
0x101010101017eull, 
0x202020202027cull,
0x404040404047aull,
0x8080808080876ull,
0x1010101010106eull,
0x2020202020205eull,
0x4040404040403eull,
0x8080808080807eull,
0x1010101017e00ull,
0x2020202027c00ull,
0x4040404047a00ull,
0x8080808087600ull,
0x10101010106e00ull,
0x20202020205e00ull,
0x40404040403e00ull,
0x80808080807e00ull,
0x10101017e0100ull,
0x20202027c0200ull,
0x40404047a0400ull,
0x8080808760800ull,
0x101010106e1000ull,
0x202020205e2000ull,
0x404040403e4000ull,
0x808080807e8000ull,
0x101017e010100ull, 
0x202027c020200ull,
0x404047a040400ull,
0x8080876080800ull,
0x1010106e101000ull,
0x2020205e202000ull,
0x4040403e404000ull,
0x8080807e808000ull,
0x1017e01010100ull,
0x2027c02020200ull,
0x4047a04040400ull,
0x8087608080800ull,
0x10106e10101000ull,
0x20205e20202000ull,
0x40403e40404000ull,
0x80807e80808000ull,
0x17e0101010100ull,
0x27c0202020200ull,
0x47a0404040400ull,
0x8760808080800ull,
0x106e1010101000ull,
0x205e2020202000ull,
0x403e4040404000ull,
0x807e8080808000ull,
0x7e010101010100ull,
0x7c020202020200ull,
0x7a040404040400ull,
0x76080808080800ull,
0x6e101010101000ull,
0x5e202020202000ull,
0x3e404040404000ull,
0x7e808080808000ull,
0x7e01010101010100ull,
0x7c02020202020200ull,
0x7a04040404040400ull,
0x7608080808080800ull,
0x6e10101010101000ull,
0x5e20202020202000ull,
0x3e40404040404000ull,
0x7e80808080808000ull};

std::array<Bitboard, 64>bishop_mask = {
0x40201008040200ull, 
0x402010080400ull,
0x4020100a00ull,
0x40221400ull,
0x2442800ull,
0x204085000ull,
0x20408102000ull,
0x2040810204000ull,
0x20100804020000ull,
0x40201008040000ull,
0x4020100a0000ull,
0x4022140000ull,
0x244280000ull,
0x20408500000ull,
0x2040810200000ull,
0x4081020400000ull,
0x10080402000200ull,
0x20100804000400ull,
0x4020100a000a00ull,
0x402214001400ull,
0x24428002800ull,
0x2040850005000ull,
0x4081020002000ull,
0x8102040004000ull,
0x8040200020400ull,
0x10080400040800ull,
0x20100a000a1000ull,
0x40221400142200ull,
0x2442800284400ull,
0x4085000500800ull,
0x8102000201000ull,
0x10204000402000ull,
0x4020002040800ull,
0x8040004081000ull,
0x100a000a102000ull,
0x22140014224000ull,
0x44280028440200ull,
0x8500050080400ull,
0x10200020100800ull,
0x20400040201000ull,
0x2000204081000ull,
0x4000408102000ull,
0xa000a10204000ull,
0x14001422400000ull,
0x28002844020000ull,
0x50005008040200ull,
0x20002010080400ull,
0x40004020100800ull,
0x20408102000ull,
0x40810204000ull,
0xa1020400000ull,
0x142240000000ull,
0x284402000000ull,
0x500804020000ull,
0x201008040200ull,
0x402010080400ull,
0x2040810204000ull,
0x4081020400000ull,
0xa102040000000ull, 
0x14224000000000ull,
0x28440200000000ull,
0x50080402000000ull,
0x20100804020000ull,
0x40201008040200ull
};

constexpr std::array<Bitboard, 64>rook_magic = {
0x28001804001502cull, 
0x40022001403002ull,
0x9080200082183000ull,
0xa00102040280600ull,
0x8100040800500300ull,
0x1100020100040008ull,
0xa00040500a84200ull,
0x210000220c408100ull,
0x24801040008420ull,
0x3000804000806008ull,
0x8914801000200080ull,
0x1b1801000800800ull,
0x30800800040180ull,
0xa82002600100844ull,
0x2001000c01000200ull,
0x1081801040800100ull,
0x10401080008a4020ull,
0xa362860026410206ull,
0x808020021000ull,
0x90010010260ull,
0x80080040280c8ull,
0x104008002008014ull,
0x400040010011846ull,
0x412820009610084ull,
0x400080008664ull,
0x81008200422200ull,
0x8220001100210040ull,
0x1215890100205000ull,
0x80080040080ull,
0x1820002000c1108ull,
0x812000a00040835ull,
0x28094600290084ull,
0x222401020800088ull,
0x18c401000402001ull,
0x480100084802002ull,
0x80080801000ull,
0x804400800800ull,
0x600800400800a00ull,
0x1001001c400080aull,
0x4002040282000241ull,
0x400020808008ull,
0x48a0601000414000ull,
0x208200420050ull,
0x1000a10110010008ull,
0x120310008010004ull,
0x24008200808024ull,
0x1102000401020088ull,
0x810001b0410002ull,
0x40800500204100ull,
0x2500408e0a00ull,
0x8000100084600080ull,
0x100200604210ca00ull,
0x1088008008040280ull,
0x2001014080200ull,
0x9002200043100ull,
0x1c00040181004200ull,
0x8440490020108001ull,
0x18d028040003421ull,
0x1012000704009ull,
0x8110001100201825ull,
0x8012002010040802ull, 
0x420041481c100aull,
0x480020809100184ull,
0x800840340208102ull};

constexpr std::array<Bitboard, 64>bishop_magic = {
0x20010222041020ull, 
0x2042041104010001ull,
0x2004282211400401ull,
0x1108084100411002ull,
0x4042108100880ull,
0x2010420800212ull,
0xa216011002306048ull,
0x42046200c4200840ull,
0x1340808084188ull,
0x440055d04040080ull,
0x102408404080ull,
0x82054401010ull,
0x100840460001406ull,
0x810420440100ull,
0x10040404828800ull,
0x2800008141082118ull,
0x8220288200412acull,
0x91088904880808c0ull,
0x54000200240100ull,
0x801800840240488cull,
0x4000a01230000ull,
0x102001088041241ull,
0x8002000c11090842ull,
0x1000213200820800ull,
0x4022100020041000ull,
0x1010080002289910ull, 
0xa000410018080505ull,
0x804004104010202ull,
0x8200e002008040ull,
0xc081024108080800ull,
0x80c410a090402ull,
0x8024288183004100ull,
0xa002084082049000ull,
0x1121442008020804ull,
0x2080402a20860ull,
0x2000200801010104ull,
0x84024010040100ull,
0x8020258080010041ull,
0x1002080106044404ull,
0x84030b0220810408ull,
0x1205041140053400ull,
0x202023024260280ull,
0x880c482088001001ull,
0x102039000804ull,
0x200924072a00c400ull,
0x10101000218840ull,
0x4008508401400480ull,
0x411a280200880020ull,
0x11c02212c200040ull,
0x45012404040c0802ull,
0x10110088040401ull,
0x440000020a80001ull,
0x1020720000ull,
0x200043042020010ull,
0x2a0149082084800ull,
0x2290030800808000ull,
0x8904c802841000ull,
0x2060201a401ull,
0x100001d202049210ull,
0x40844200940410ull,
0x208080806230420ull,
0x20e012020220980ull,
0x8027020810c0080ull,
0x420ce80488108100ull
};

Bitboard set_occupancy(int index, int bits, Bitboard mask) {
    Bitboard occupancy = 0ULL;
    Bitboard subset = mask;
    
    for (int i = 0; i < bits; i++) {
        // find the next square in the mask
        int square = lsb(subset);   // least significant set bit
        subset &= subset - 1;       // clear that bit

        // if index has this bit set → put a blocker here
        if (index & (1 << i))
            occupancy |= (1ULL << square);
    }
    return occupancy;
}

std::vector<Bitboard> generate_all_blockers(Bitboard mask) {
    std::vector<int> bits;
    for (int sq = 0; sq < 64; sq++) {
        if (mask & (1ULL << sq))
            bits.push_back(sq);
    }

    int num_bits = bits.size();
    int size = 1 << num_bits;

    std::vector<Bitboard> blockers(size);
    for (int i = 0; i < size; i++) {
        Bitboard occ = 0ULL;
        for (int j = 0; j < num_bits; j++) {
            if (i & (1 << j)) {
                occ |= (1ULL << bits[j]);
            }
        }
        blockers[i] = occ;
    }
    return blockers;
}

Bitboard compute_rook_attack(int square, Bitboard blockers) {
    Bitboard attacks = 0ULL;
    int rank = square / 8;
    int file = square % 8;

    // north
    for (int r = rank + 1; r <= 7; r++) {
        int sq = r * 8 + file;
        attacks |= 1ULL << sq;
        if (blockers & (1ULL << sq)) break; // stop at blocker
    }
    // south
    for (int r = rank - 1; r >= 0; r--) {
        int sq = r * 8 + file;
        attacks |= 1ULL << sq;
        if (blockers & (1ULL << sq)) break;
    }
    // east
    for (int f = file + 1; f <= 7; f++) {
        int sq = rank * 8 + f;
        attacks |= 1ULL << sq;
        if (blockers & (1ULL << sq)) break;
    }
    // west
    for (int f = file - 1; f >= 0; f--) {
        int sq = rank * 8 + f;
        attacks |= 1ULL << sq;
        if (blockers & (1ULL << sq)) break;
    }
    return attacks;
}

Bitboard compute_bishop_attack(int square, Bitboard blockers) {
    Bitboard attacks = 0ULL;
    int rank = square / 8;
    int file = square % 8;

    // NE (+9)
    for (int r = rank + 1, f = file + 1; r <= 7 && f <= 7; r++, f++) {
        int sq = r * 8 + f;
        attacks |= 1ULL << sq;
        if (blockers & (1ULL << sq)) break;
    }

    // NW (+7)
    for (int r = rank + 1, f = file - 1; r <= 7 && f >= 0; r++, f--) {
        int sq = r * 8 + f;
        attacks |= 1ULL << sq;
        if (blockers & (1ULL << sq)) break;
    }

    // SE (-7)
    for (int r = rank - 1, f = file + 1; r >= 0 && f <= 7; r--, f++) {
        int sq = r * 8 + f;
        attacks |= 1ULL << sq;
        if (blockers & (1ULL << sq)) break;
    }

    // SW (-9)
    for (int r = rank - 1, f = file - 1; r >= 0 && f >= 0; r--, f--) {
        int sq = r * 8 + f;
        attacks |= 1ULL << sq;
        if (blockers & (1ULL << sq)) break;
    }

    return attacks;
}


using AttackFunc = Bitboard(*)(int square, Bitboard blockers);

Bitboard find_magic(int square, Bitboard mask, AttackFunc compute_attack) {
    int relevant_bits = __builtin_popcountll(mask);
    int size = 1 << relevant_bits;
    std::vector<Bitboard> attacks(size);
    std::vector<int> used(size, -1);

    std::vector<Bitboard> blockers = generate_all_blockers(mask);

    for (int i = 0; i < size; i++)
        attacks[i] = compute_attack(square, blockers[i]);

    std::mt19937_64 rng(std::random_device{}());

    for (;;) {
        uint64_t magic = rng() & rng() & rng();
        bool fail = false;
        fill(used.begin(), used.end(), -1);

        for (int i = 0; i < size; i++) {
            int index = (blockers[i] * magic) >> (64 - relevant_bits);
            if (used[index] == -1)
                used[index] = i;
            else if (attacks[i] != attacks[used[index]]) {
                fail = true;
                break;
            }
        }
        if (!fail) return magic;
    }
}

constexpr auto generate_rook_attacks_for_square(int sq) {
    std::array<Bitboard, 4096> attacks = {};
    Bitboard m = rook_mask[sq];
    int relevantBits = __builtin_popcountll(m);
    int size = 1 << relevantBits;

    for (int index = 0; index < size; index++) {
        Bitboard blockers = set_occupancy(index, relevantBits, m);

        Bitboard attack = compute_rook_attack(sq, blockers);

        uint64_t magicIndex = (blockers * rook_magic[sq]) >> (64 - relevantBits);

        attacks[magicIndex] = attack;
    }

    return attacks;
}
constexpr auto init_rook_attacks(){
    std::array<std::array<Bitboard, 4096>, 64> rook_attacks = {};
    for (int sq = 0; sq < 64; sq++){
        rook_attacks[sq] = generate_rook_attacks_for_square(sq);
    }

    return rook_attacks;
}
constexpr auto generate_bishop_attacks_for_square(int sq) {
    std::array<Bitboard, 512> attacks = {};
    Bitboard m = bishop_mask[sq];
    int relevantBits = __builtin_popcountll(m);
    int size = 1 << relevantBits;

    for (int index = 0; index < size; index++) {
        Bitboard blockers = set_occupancy(index, relevantBits, m);

        Bitboard attack = compute_bishop_attack(sq, blockers);

        uint64_t magicIndex = (blockers * bishop_magic[sq]) >> (64 - relevantBits);

        if (magicIndex < attacks.size()) // avoid out-of-bounds
            attacks[magicIndex] = attack;
    }

    return attacks;
}
constexpr auto init_bishop_attacks(){
    std::array<std::array<Bitboard, 512>, 64> bishop_attacks = {};
    for (int sq = 0; sq < 64; sq++){
        bishop_attacks[sq] = generate_bishop_attacks_for_square(sq);
    }

    return bishop_attacks;
}

std::array<std::array<Bitboard, 4096>, 64>rook_attacks = init_rook_attacks();
std::array<std::array<Bitboard, 512>, 64>bishop_attacks = init_bishop_attacks();