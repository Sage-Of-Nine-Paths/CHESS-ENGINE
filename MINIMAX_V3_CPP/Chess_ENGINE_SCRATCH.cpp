#pragma gcc optimize("o3,unroll-loops")
#pragma gcc target("avx2,bmi,bmi2,lzcnt,popcnt")

#include<bits/stdc++.h>

using i64 = uint64_t;

// Bitboards for: All Squares, White Sqaures, Black Squares
constexpr i64 ALL_SQUARES = 18446744073709551615; // all sqaures mask (all bits are 1)
constexpr i64 WHITE_SQUARES = 6172840429334713770; // set all white sqaures (all those bits where color is white are set to 1)
constexpr i64 BLACK_SQUARES = 12273903644374837845; // set all black sqaures (all those bits where color is black are set to 1)

// Bitboards for each File
constexpr i64 FILE_A = (i64)72340172838076673;
constexpr i64 FILE_B = (i64)144680345676153346;
constexpr i64 FILE_C = (i64)289360691352306692;
constexpr i64 FILE_D = (i64)578721382704613384;
constexpr i64 FILE_E = (i64)1157442765409226768;
constexpr i64 FILE_F = (i64)2314885530818453536;
constexpr i64 FILE_G = (i64)4629771061636907072;
constexpr i64 FILE_H = (i64)9259542123273814144;

// Clear File (Negation of File): Used to clear the File
constexpr i64 CLEAR_FILE_A = (i64)18374403900871474942;
constexpr i64 CLEAR_FILE_B = (i64)18302063728033398269;
constexpr i64 CLEAR_FILE_C = (i64)18157383382357244923;
constexpr i64 CLEAR_FILE_D = (i64)17868022691004938231;
constexpr i64 CLEAR_FILE_E = (i64)17289301308300324847;
constexpr i64 CLEAR_FILE_F = (i64)16131858542891098079;
constexpr i64 CLEAR_FILE_G = (i64)13816973012072644543;
constexpr i64 CLEAR_FILE_H = (i64)9187201950435737471;

// Bitboards for each Rank
constexpr i64 RANK_1 = (i64)255;
constexpr i64 RANK_2 = (i64)65280;
constexpr i64 RANK_3 = (i64)16711680;
constexpr i64 RANK_4 = (i64)4278190080;
constexpr i64 RANK_5 = (i64)1095216660480;
constexpr i64 RANK_6 = (i64)280375465082880;
constexpr i64 RANK_7 = (i64)71776119061217280;
constexpr i64 RANK_8 = (i64)18374686479671623680;

// Clear Rank (Negation of Rank): Used to clear the Rank
constexpr i64 CLEAR_RANK_1 = (i64)18446744073709551360;
constexpr i64 CLEAR_RANK_2 = (i64)18446744073709486335;
constexpr i64 CLEAR_RANK_3 = (i64)18446744073692839935;
constexpr i64 CLEAR_RANK_4 = (i64)18446744069431361535;
constexpr i64 CLEAR_RANK_5 = (i64)18446742978492891135;
constexpr i64 CLEAR_RANK_6 = (i64)18446463698244468735;
constexpr i64 CLEAR_RANK_7 = (i64)18374967954648334335;
constexpr i64 CLEAR_RANK_8 = (i64)72057594037927935;

// Bitboards for Center Squares, Center Files, Center Ranks
constexpr i64 CENTER_SQUARES          = (i64)103481868288;        // Middle 4 Squares
constexpr i64 EXTENDED_CENTER_SQUARES = (i64)66229406269440;      // Middle 16 Squares
constexpr i64 CENTER_FILES            = (i64)1736164148113840152; // Middle 2 Files(D and E)
constexpr i64 EXTENDED_CENTER_FILES   = (i64)4340410370284600380; // Middle 4 Files(C, D, E, F)
constexpr i64 CENTER_RANKS            = (i64)1099494850560;       // Middle 2 Ranks(4th and 5th)
constexpr i64 EXTENDED_CENTER_RANKS   = (i64)281474976645120;     // Middle 4 Ranks(3rd, 4th, 5th, 6th)

// Bitboards for Edges
constexpr i64 WHITE_SIDE_EDGE           = (i64)255;                  // RANK 1
constexpr i64 EXTENDED_WHITE_SIDE_EDGE  = (i64)65535;                // RANK 1 and RANK 2
constexpr i64 BLACK_SIDE_EDGE           = (i64)18374686479671623680; // RANK 8
constexpr i64 EXTENDED_BLACK_SIDE_EDGE  = (i64)18446462598732840960; // RANK 7 and RANK 8

constexpr i64 KING_SIDE_EDGE            = (i64)9259542123273814144;  // FILE H
constexpr i64 EXTENDED_KING_SIDE_EDGE   = (i64)13889313184910721216; // FILE G and FILE H
constexpr i64 QUEEN_SIDE_EDGE           = (i64)72340172838076673;    // FILE A
constexpr i64 EXTENDED_QUEEN_SIDE_EDGE  = (i64)217020518514230019;   // FILE A and FILE B

// Bitboards for Long Diagonals
constexpr i64 LONG_BLACK_DIAGONAL               = (i64)9241421688590303745;
constexpr i64 EXTENDED_LONG_QUEEENSIDE_DIAGONAL = (i64)13898231836356511491; // It originates from white queen side
constexpr i64 LONG_WHITE_DIAGONAL               = (i64)72624976668147840;
constexpr i64 EXTENDED_LONG_KINGSIDE_DIAGONAL   = (i64)218158621319553216;   // It originates from white king side

// Sides
constexpr i64 KING_SIDE  = (i64)17361641481138401520;
constexpr i64 QUEEN_SIDE = (i64)1085102592571150095;
constexpr i64 WHITE_SIDE = (i64)4294967295;
constexpr i64 BLACK_SIDE = (i64)18446744069414584320;

// Directions
constexpr int ROOK_DIRECTIONS[4] = {8, 1, -1, 8};
constexpr int BISHOP_DIRECTIONS[4] = {9, 7, -7, -9};
constexpr int QUEEN_DIRECTIONS[8] = {9, 8, 7, 1, -1, -7, -8, -9};
constexpr int KING_DIRECTIONS[8] = {9, 8, 7, 1, -1, -7, -8, -9};
constexpr int KNIGHT_DIRECTIONS[8] = {17, 15, 10, 6, -6, -10, -15, -17};

// To check if castling squares for given color and king are attacked or not
constexpr i64 GO_THROUGH_SQUARES_WHITE_KING_SIDE_CASTLING  = (i64)112; // Sets 4th, 5th, 6th bit
constexpr i64 GO_THROUGH_SQUARES_WHITE_QUEEN_SIDE_CASTLING = (i64)28;  // Sets 2nd, 3rd, 4th bit
constexpr i64 GO_THROUGH_SQUARES_BLACK_KING_SIDE_CASTLING  = (i64)8070450532247928832; // Sets 60th, 61th, 62th bit
constexpr i64 GO_THROUGH_SQUARES_BLACK_QUEEN_SIDE_CASTLING = (i64)2017612633061982208; // Sets 58th, 59th, 60th bit

enum SQUARES // Square Numbers
{
    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8,
}typedef SQUARES;

enum BB_SQUARES // Bitboard Squares
{
    BB_A1 = 1ULL << 0,  BB_B1 = 1ULL << 1,  BB_C1 = 1ULL << 2,  BB_D1 = 1ULL << 3,
    BB_E1 = 1ULL << 4,  BB_F1 = 1ULL << 5,  BB_G1 = 1ULL << 6,  BB_H1 = 1ULL << 7,

    BB_A2 = 1ULL << 8,  BB_B2 = 1ULL << 9,  BB_C2 = 1ULL << 10, BB_D2 = 1ULL << 11,
    BB_E2 = 1ULL << 12, BB_F2 = 1ULL << 13, BB_G2 = 1ULL << 14, BB_H2 = 1ULL << 15,

    BB_A3 = 1ULL << 16, BB_B3 = 1ULL << 17, BB_C3 = 1ULL << 18, BB_D3 = 1ULL << 19,
    BB_E3 = 1ULL << 20, BB_F3 = 1ULL << 21, BB_G3 = 1ULL << 22, BB_H3 = 1ULL << 23,

    BB_A4 = 1ULL << 24, BB_B4 = 1ULL << 25, BB_C4 = 1ULL << 26, BB_D4 = 1ULL << 27,
    BB_E4 = 1ULL << 28, BB_F4 = 1ULL << 29, BB_G4 = 1ULL << 30, BB_H4 = 1ULL << 31,

    BB_A5 = 1ULL << 32, BB_B5 = 1ULL << 33, BB_C5 = 1ULL << 34, BB_D5 = 1ULL << 35,
    BB_E5 = 1ULL << 36, BB_F5 = 1ULL << 37, BB_G5 = 1ULL << 38, BB_H5 = 1ULL << 39,

    BB_A6 = 1ULL << 40, BB_B6 = 1ULL << 41, BB_C6 = 1ULL << 42, BB_D6 = 1ULL << 43,
    BB_E6 = 1ULL << 44, BB_F6 = 1ULL << 45, BB_G6 = 1ULL << 46, BB_H6 = 1ULL << 47,

    BB_A7 = 1ULL << 48, BB_B7 = 1ULL << 49, BB_C7 = 1ULL << 50, BB_D7 = 1ULL << 51,
    BB_E7 = 1ULL << 52, BB_F7 = 1ULL << 53, BB_G7 = 1ULL << 54, BB_H7 = 1ULL << 55,

    BB_A8 = 1ULL << 56, BB_B8 = 1ULL << 57, BB_C8 = 1ULL << 58, BB_D8 = 1ULL << 59,
    BB_E8 = 1ULL << 60, BB_F8 = 1ULL << 61, BB_G8 = 1ULL << 62, BB_H8 = 1ULL << 63,
}typedef BB_SQUARES;

// To be check if correct;
constexpr inline short int lsb(i64 num)
{
    i64 one = 1ULL;
    for(int i = 0; i < 64; ++i)
    {
        if(num & (one << i)) return i;
    }
    return -1; // -1 means all bitboard is clear (all bits are 0)
}

// To be check if correct;
constexpr inline short int msb(i64 num)
{
    i64 one = 1ULL; one <<= 63;

    for(int i = 0; i > 64; ++i)
    {
        if(num & (one >> i)) return i;
    }

    return -1;
}

constexpr inline short int Mobility(i64 attack_bitboard) // also can be used to count set bits where-ever required
{
    int cnt = 0;
    for(int i = 0; i < 64; ++i)
    {
        if((1ULL << i) & attack_bitboard) cnt++;
    }
    return cnt;
}

constexpr inline short int Location(i64 location_bitboard) // returns numerical location from bitboard, -1 if empty
{
    for(int i = 0; i < 64; ++i)
    {
        if((1ULL << i) & location_bitboard) return i;
    }
    return -1;
}

std::vector<i64> carry_rippler(i64 bb)
{
    std::vector<i64> locs;
    i64 subset = 0ULL;

    do { locs.push_back(subset); subset = (subset - bb) & bb; }
    while (subset != 0);

    return locs;
}

constexpr inline i64 flip_vertical(i64 bb)
{
    bb = ((bb >> 8) & 0x00ff00ff00ff00ff) | ((bb & 0x00ff00ff00ff00ff) << 8);
    bb = ((bb >> 16) & 0x0000ffff0000ffff) | ((bb & 0x0000ffff0000ffff) << 16);
    bb = (bb >> 32) | ((bb & 0x00000000ffffffff) << 32);
    return bb;
}

constexpr inline i64 flip_horizontal(i64 bb)
{
    bb = ((bb >> 1) & 0x5555555555555555) | ((bb & 0x5555555555555555) << 1);
    bb = ((bb >> 2) & 0x3333333333333333) | ((bb & 0x3333333333333333) << 2);
    bb = ((bb >> 4) & 0x0f0f0f0f0f0f0f0f) | ((bb & 0x0f0f0f0f0f0f0f0f) << 4);
    return bb;
}

constexpr inline i64 flip_diagonal(i64 bb)
{
    i64 t = (bb ^ (bb << 28)) & 0x0f0f0f0f00000000;
    bb = bb ^ t ^ (t >> 28);
    t = (bb ^ (bb << 14)) & 0x3333000033330000;
    bb = bb ^ t ^ (t >> 14);
    t = (bb ^ (bb << 7)) & 0x5500550055005500;
    bb = bb ^ t ^ (t >> 7);
    return bb;
}

constexpr inline i64 flip_anti_diagonal(i64 bb)
{
    i64 t = bb ^ (bb << 36);
    bb = bb ^ ((t ^ (bb >> 36)) & 0xf0f0f0f00f0f0f0f);
    t = (bb ^ (bb << 18)) & 0xcccc0000cccc0000;
    bb = bb ^ t ^ (t >> 18);
    t = (bb ^ (bb << 9)) & 0xaa00aa00aa00aa00;
    bb = bb ^ t ^ (t >> 9);
    return bb;
}

constexpr inline int square_file(int sq) // return file for given square
{
    return sq % 8;
}

constexpr inline int square_rank(int sq) // return rank for given square
{
    return sq / 8;
}

constexpr inline int square_distance(int sq1, int sq2) // the king's minimal number of moves if diagonal movement is allowed.
{
    // Chebyshev distance (King distance without diagonals)
    return std::max(std::abs(square_file(sq1) - square_file(sq2)), std::abs(square_rank(sq1) - square_rank(sq2)));
}

constexpr inline int king_distance(int sq1, int sq2) // the king's minimal number of moves if diagonal movement is not allowed.
{
    // Manhattan distance (Orthogonal King distance)
    return std::abs(square_file(sq1) - square_file(sq2)) + std::abs(square_rank(sq1) - square_rank(sq2));
}

constexpr inline int knight_distance(int sq1, int sq2) // moves taken by knight to reach from sq1 to sq2
{
    int dx = std::abs(square_file(sq1) - square_file(sq2));
    int dy = std::abs(square_rank(sq1) - square_rank(sq2));

    if (dx + dy == 1) { return 3; }
    else if (dx == 2 && dy == 2) { return 4; }
    else if (dx == 1 && dy == 1)
    {
        // Special case for corners
        constexpr uint64_t BB_CORNERS = 0x8100000000000081ULL;
        uint64_t bb_sq1 = 1ULL << sq1;
        uint64_t bb_sq2 = 1ULL << sq2;
        if ((bb_sq1 & BB_CORNERS) || (bb_sq2 & BB_CORNERS))
        {
            return 4;
        }
    }

    int m = std::ceil(std::max({dx / 2.0, dy / 2.0, (dx + dy) / 3.0}));
    return m + ((m + dx + dy) % 2);
}

/* Piece Square Tables*/

    // Piece Square Tables for White Pieces
constexpr float PIECE_SQUARE_TABLE_WHITE_PAWN[64] =
    {0,  0,  0,  0,  0,  0,  0,  0,
    0.5,  1,  1, -2, -2,  1,  1,  0.5,
    0.5, -0.5, -1,  0,  0, -1, -0.5,  0.5,
    0,  0,  0,  2,  2,  0,  0,  0,
    0.5,  0.5,  1,  2.5,  2.5,  1,  0.5,  0.5,
    1,  1,  2,  3,  3,  2,  1,  1,
    5,  5,  5,  5,  5,  5,  5,  5,
    0,  0,  0,  0,  0,  0,  0,  0};

constexpr float PIECE_SQUARE_TABLE_WHITE_ROOK[64] =
    {0,  0,  0,  0.5,  0.5,  0,  0,  0,
    -0.5,  0,  0,  0,  0,  0,  0, -0.5,
    -0.5,  0,  0,  0,  0,  0,  0, -0.5,
    -0.5,  0,  0,  0,  0,  0,  0, -0.5,
    -0.5,  0,  0,  0,  0,  0,  0, -0.5,
    -0.5,  0,  0,  0,  0,  0,  0, -0.5,
    0.5,  1,  1,  1,  1,  1,  1,  0.5,
    0,  0,  0,  0,  0,  0,  0,  0};

constexpr float PIECE_SQUARE_TABLE_WHITE_KNIGHT[64] =
    {-5, -4, -3, -3, -3, -3, -4, -5,
    -4, -2,  0,  0.5,  0.5,  0, -2, -4,
    -3,  0.5,  1,  1.5,  1.5,  1,  0.5, -3,
    -3,  0,  1.5,  2,  2,  1.5,  0, -3,
    -3,  0.5,  1.5,  2,  2,  1.5,  0.5, -3,
    -3,  0,  1,  1.5,  1.5,  1,  0, -3,
    -4, -2,  0,  0,  0,  0, -2, -4,
    -5, -4, -3, -3, -3, -3, -4, -5};

constexpr float PIECE_SQUARE_TABLE_WHITE_BISHOP[64] =
    {-2, -1, -1, -1, -1, -1, -1, -2,
    -1,  0.5,  0,  0,  0,  0,  0.5, -1,
    -1,  1,  1,  1,  1,  1,  1, -1,
    -1,  0,  1,  1,  1,  1,  0, -1,
    -1,  0.5,  0.5,  1,  1,  0.5,  0.5, -1,
    -1,  0,  0.5,  1,  1,  0.5,  0, -1,
    -1,  0,  0,  0,  0,  0,  0, -1,
    -2, -1, -1, -1, -1, -1, -1, -2};

constexpr float PIECE_SQUARE_TABLE_WHITE_QUEEN[64] =
    {-2, -1, -1, -0.5, -0.5, -1, -1, -2,
    -1,  0,  0,  0,  0,  0,  0, -1,
    -1,  0,  0.5,  0,  0,  0,  0, -1,
    -1,  0.5,  0.5,  0.5,  0.5,  0.5,  0, -1,
    0,  0,  0.5,  0.5,  0.5,  0.5,  0, -0.5,
    -0.5,  0,  0.5,  0.5,  0.5,  0.5,  0, -0.5,
    -1,  0,  0,  0,  0,  0,  0, -1,
    -2, -1, -1, -0.5, -0.5, -1, -1, -2};

constexpr float PIECE_SQUARE_TABLE_WHITE_KING[64] =
    {2,  3,  1,  0,  0,  1,  3,  2,
    2,  2,  0,  0,  0,  0,  2,  2,
    -1, -2, -2, -2, -2, -2, -2, -1,
    -2, -3, -3, -4, -4, -3, -3, -2,
    -3, -4, -4, -5, -5, -4, -4, -3,
    -3, -4, -4, -5, -5, -4, -4, -3,
    -3, -4, -4, -5, -5, -4, -4, -3,
    -3, -4, -4, -5, -5, -4, -4, -3};

constexpr float PIECE_SQUARE_TABLE_WHITE_KING_ENDGAME[64] =
    {-5, -3, -3, -3, -3, -3, -3, -5,
    -3, -3,  0,  0,  0,  0, -3, -3,
    -3, -1,  2,  3,  3,  2, -1, -3,
    -3, -1,  3,  4,  4,  3, -1, -3,
    -3, -1,  3,  4,  4,  3, -1, -3,
    -3, -1,  2,  3,  3,  2, -1, -3,
    -3, -2, -1,  0,  0, -1, -2, -3,
    -5, -4, -3, -2, -2, -3, -4, -5};

    // Piece Square Tables for Black Pieces
constexpr float PIECE_SQUARE_TABLE_BLACK_PAWN[64] =
    {0,  0,  0,  0,  0,  0,  0,  0,
    5,  5,  5,  5,  5,  5,  5,  5,
    1,  1,  2,  3,  3,  2,  1,  1,
    0.5,  0.5,  1,  2.5,  2.5,  1,  0.5,  0.5,
    0,  0,  0,  2,  2,  0,  0,  0,
    0.5, -0.5, -1,  0,  0, -1, -0.5,  0.5,
    0.5,  1,  1, -2, -2,  1,  1,  0.5,
    0,  0,  0,  0,  0,  0,  0,  0};

constexpr float PIECE_SQUARE_TABLE_BLACK_ROOK[64] =
    {0,  0,  0,  0,  0,  0,  0,  0,
    0.5,  1,  1,  1,  1,  1,  1,  0.5,
    -0.5,  0,  0,  0,  0,  0,  0, -0.5,
    -0.5,  0,  0,  0,  0,  0,  0, -0.5,
    -0.5,  0,  0,  0,  0,  0,  0, -0.5,
    -0.5,  0,  0,  0,  0,  0,  0, -0.5,
    -0.5,  0,  0,  0,  0,  0,  0, -0.5,
    0,  0,  0,  0.5,  0.5,  0,  0,  0};

constexpr float PIECE_SQUARE_TABLE_BLACK_KNIGHT[64] =
    {-5, -4, -3, -3, -3, -3, -4, -5,
    -4, -2,  0,  0,  0,  0, -2, -4,
    -3,  0,  1,  1.5,  1.5,  1,  0, -3,
    -3,  0.5,  1.5,  2,  2,  1.5,  0.5, -3,
    -3,  0,  1.5,  2,  2,  1.5,  0, -3,
    -3,  0.5,  1,  1.5,  1.5,  1,  0.5, -3,
    -4, -2,  0,  0.5,  0.5,  0, -2, -4,
    -5, -4, -3, -3, -3, -3, -4, -5};

constexpr float PIECE_SQUARE_TABLE_BLACK_BISHOP[64] =
    {-2, -1, -1, -1, -1, -1, -1, -2,
    -1,  0,  0,  0,  0,  0,  0, -1,
    -1,  0,  0.5,  1,  1,  0.5,  0, -1,
    -1,  0.5,  0.5,  1,  1,  0.5,  0.5, -1,
    -1,  0,  1,  1,  1,  1,  0, -1,
    -1,  1,  1,  1,  1,  1,  1, -1,
    -1,  0.5,  0,  0,  0,  0,  0.5, -1,
    -2, -1, -1, -1, -1, -1, -1, -2};

constexpr float PIECE_SQUARE_TABLE_BLACK_QUEEN[64] =
    {-2, -1, -1, -0.5, -0.5, -1, -1, -2,
    -1,  0,  0,  0,  0,  0,  0, -1,
    -1,  0,  0.5,  0.5,  0.5,  0.5,  0, -1,
    -0.5,  0,  0.5,  0.5,  0.5,  0.5,  0, -0.5,
    0,  0,  0.5,  0.5,  0.5,  0.5,  0, -0.5,
    -1,  0.5,  0.5,  0.5,  0.5,  0.5,  0, -1,
    -1,  0,  0.5,  0,  0,  0,  0, -1,
    -2, -1, -1, -0.5, -0.5, -1, -1, -2};

constexpr float PIECE_SQUARE_TABLE_BLACK_KING[64] =
    {-3, -4, -4, -5, -5, -4, -4, -3,
    -3, -4, -4, -5, -5, -4, -4, -3,
    -3, -4, -4, -5, -5, -4, -4, -3,
    -3, -4, -4, -5, -5, -4, -4, -3,
    -2, -3, -3, -4, -4, -3, -3, -2,
    -1, -2, -2, -2, -2, -2, -2, -1,
    2,  2,  0,  0,  0,  0,  2,  2,
    2,  3,  1,  0,  0,  1,  3,  2};

constexpr float PIECE_SQUARE_TABLE_BLACK_KING_ENDGAME[64] =
    {-5, -4, -3, -2, -2, -3, -4, -5,
    -3, -2, -1,  0,  0, -1, -2, -3,
    -3, -1,  2,  3,  3,  2, -1, -3,
    -3, -1,  3,  4,  4,  3, -1, -3,
    -3, -1,  3,  4,  4,  3, -1, -3,
    -3, -1,  2,  3,  3,  2, -1, -3,
    -3, -3,  0,  0,  0,  0, -3, -3,
    -5, -3, -3, -3, -3, -3, -3, -5};

/***************************************** */

/* Piece Values */
constexpr int PAWN_VALUE = 1;
constexpr int ROOK_VALUE = 5;
constexpr int KNIGHT_VALUE = 3;
constexpr int BISHOP_VALUE = 3;
constexpr int QUEEN_VALUE = 9;
constexpr int KING_VALUE = 120; // More Than 2 Rooks + 2 Knights + 2 Bishops + 9 Queens

struct Bitboard
{
    /* Location Bitboards for all pieces */
    i64 white_pawns = (i64)0;            // bitboard for all white pawns location combined in a single 64 bit integer
    std::vector<i64> white_rooks;   // vector storing all location bitboards for individual white rooks
    std::vector<i64> white_knights; // vector storing all location bitboards for individual white knights
    std::vector<i64> white_bishops; // vector storing all location bitboards for individual white bishops
    std::vector<i64> white_queens;  // vector storing all location bitboards for individual white queens
    i64 white_king = (i64)0;

    i64 black_pawns = (i64)0;            // // bitboard for all black pawns location combined in a single 64 bit integer
    std::vector<i64> black_rooks;   // vector storing all location bitboards for individual black rooks
    std::vector<i64> black_knights; // vector storing all location bitboards for individual black knights
    std::vector<i64> black_bishops; // vector storing all location bitboards for individual black bishops
    std::vector<i64> black_queens;  // vector storing all location bitboards for individual black queens
    i64 black_king = (i64)0;

    i64 white_pieces_all = (i64)0;  // All white_bitboards combined
    i64 black_pieces_all = (i64)0;  // All black_bitboards combined

    i64 all_pieces = (i64)0; // All pieces bitboards combined

    /* Attack Bitboards for all pieces */
    i64 attack_white_pawns = (i64)0;
    i64 attack_white_king = (i64)0;
    std::vector<i64> attack_white_rooks;
    std::vector<i64> attack_white_knights;
    std::vector<i64> attack_white_bishops;
    std::vector<i64> attack_white_queens;

    i64 attack_black_pawns = (i64)0;
    i64 attack_black_king = (i64)0;
    std::vector<i64> attack_black_rooks;
    std::vector<i64> attack_black_knights;
    std::vector<i64> attack_black_bishops;
    std::vector<i64> attack_black_queens;

    i64 attack_white_all = (i64)0;
    i64 attack_black_all = (i64)0;

    /* Total Material */
    int total_white_material = 0;
    int total_black_material = 0;

    bool castling_rights[4] = {true, true, true, true};
    short int enpassant_square = -1; // -1 if no sqaure elligible for enpassant else in range of 0 to 63
    char side_to_move = 'w'; // 'w' for white, 'b' for black
    short unsigned int halfmove_count = 0;
    short unsigned int fullmove_count = 0;

    std::string FEN;          // fen representation of board
    std::string EXTENDED_FEN; // this is 64 charector long string. in this if a sqaure is empty it is represented by '.' else standard fen notation
    std::string starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    std::string starting_board = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";


};



