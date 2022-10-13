#if !defined(VM_HEADER_IR_BE_INT3)
#define VM_HEADER_IR_BE_INT3

#include <stdint.h>
#include "../ir.h"

enum {
    VM_OPCODE_ADD_I8_REG_REG = 1,
    VM_OPCODE_ADD_I8_REG_CONST = 2,
    VM_OPCODE_ADD_I8_CONST_REG = 3,
    VM_OPCODE_ADD_I8_CONST_CONST = 4,
    VM_OPCODE_SUB_I8_REG_REG = 5,
    VM_OPCODE_SUB_I8_REG_CONST = 6,
    VM_OPCODE_SUB_I8_CONST_REG = 7,
    VM_OPCODE_SUB_I8_CONST_CONST = 8,
    VM_OPCODE_MUL_I8_REG_REG = 9,
    VM_OPCODE_MUL_I8_REG_CONST = 10,
    VM_OPCODE_MUL_I8_CONST_REG = 11,
    VM_OPCODE_MUL_I8_CONST_CONST = 12,
    VM_OPCODE_DIV_I8_REG_REG = 13,
    VM_OPCODE_DIV_I8_REG_CONST = 14,
    VM_OPCODE_DIV_I8_CONST_REG = 15,
    VM_OPCODE_DIV_I8_CONST_CONST = 16,
    VM_OPCODE_MOD_I8_REG_REG = 17,
    VM_OPCODE_MOD_I8_REG_CONST = 18,
    VM_OPCODE_MOD_I8_CONST_REG = 19,
    VM_OPCODE_MOD_I8_CONST_CONST = 20,
    VM_OPCODE_EQ_I8_REG_REG = 21,
    VM_OPCODE_EQ_I8_REG_CONST = 22,
    VM_OPCODE_EQ_I8_CONST_REG = 23,
    VM_OPCODE_EQ_I8_CONST_CONST = 24,
    VM_OPCODE_LT_I8_REG_REG = 25,
    VM_OPCODE_LT_I8_REG_CONST = 26,
    VM_OPCODE_LT_I8_CONST_REG = 27,
    VM_OPCODE_LT_I8_CONST_CONST = 28,
    VM_OPCODE_BB_I8_REG_REG = 29,
    VM_OPCODE_BB_I8_REG_CONST = 30,
    VM_OPCODE_BB_I8_CONST_REG = 31,
    VM_OPCODE_BB_I8_CONST_CONST = 32,
    VM_OPCODE_BEQ_I8_REG_REG = 33,
    VM_OPCODE_BEQ_I8_REG_CONST = 34,
    VM_OPCODE_BEQ_I8_CONST_REG = 35,
    VM_OPCODE_BEQ_I8_CONST_CONST = 36,
    VM_OPCODE_BLT_I8_REG_REG = 37,
    VM_OPCODE_BLT_I8_REG_CONST = 38,
    VM_OPCODE_BLT_I8_CONST_REG = 39,
    VM_OPCODE_BLT_I8_CONST_CONST = 40,
    VM_OPCODE_MOVE_I8_REG = 41,
    VM_OPCODE_MOVE_I8_CONST = 42,
    VM_OPCODE_OUT_I8_REG = 43,
    VM_OPCODE_OUT_I8_CONST = 44,
    VM_OPCODE_IN_I8_VOID = 45,
    VM_OPCODE_RET_I8_REG = 46,
    VM_OPCODE_RET_I8_CONST = 47,
    VM_OPCODE_TYPE_I8_REG = 48,
    VM_OPCODE_TYPE_I8_CONST = 49,
    VM_OPCODE_BNOT_I8_REG = 50,
    VM_OPCODE_BNOT_I8_CONST = 51,
    VM_OPCODE_BOR_I8_REG_REG = 52,
    VM_OPCODE_BOR_I8_REG_CONST = 53,
    VM_OPCODE_BOR_I8_CONST_REG = 54,
    VM_OPCODE_BOR_I8_CONST_CONST = 55,
    VM_OPCODE_BXOR_I8_REG_REG = 56,
    VM_OPCODE_BXOR_I8_REG_CONST = 57,
    VM_OPCODE_BXOR_I8_CONST_REG = 58,
    VM_OPCODE_BXOR_I8_CONST_CONST = 59,
    VM_OPCODE_BAND_I8_REG_REG = 60,
    VM_OPCODE_BAND_I8_REG_CONST = 61,
    VM_OPCODE_BAND_I8_CONST_REG = 62,
    VM_OPCODE_BAND_I8_CONST_CONST = 63,
    VM_OPCODE_BSHL_I8_REG_REG = 64,
    VM_OPCODE_BSHL_I8_REG_CONST = 65,
    VM_OPCODE_BSHL_I8_CONST_REG = 66,
    VM_OPCODE_BSHL_I8_CONST_CONST = 67,
    VM_OPCODE_BSHR_I8_REG_REG = 68,
    VM_OPCODE_BSHR_I8_REG_CONST = 69,
    VM_OPCODE_BSHR_I8_CONST_REG = 70,
    VM_OPCODE_BSHR_I8_CONST_CONST = 71,
    VM_OPCODE_ADD_I16_REG_REG = 72,
    VM_OPCODE_ADD_I16_REG_CONST = 73,
    VM_OPCODE_ADD_I16_CONST_REG = 74,
    VM_OPCODE_ADD_I16_CONST_CONST = 75,
    VM_OPCODE_SUB_I16_REG_REG = 76,
    VM_OPCODE_SUB_I16_REG_CONST = 77,
    VM_OPCODE_SUB_I16_CONST_REG = 78,
    VM_OPCODE_SUB_I16_CONST_CONST = 79,
    VM_OPCODE_MUL_I16_REG_REG = 80,
    VM_OPCODE_MUL_I16_REG_CONST = 81,
    VM_OPCODE_MUL_I16_CONST_REG = 82,
    VM_OPCODE_MUL_I16_CONST_CONST = 83,
    VM_OPCODE_DIV_I16_REG_REG = 84,
    VM_OPCODE_DIV_I16_REG_CONST = 85,
    VM_OPCODE_DIV_I16_CONST_REG = 86,
    VM_OPCODE_DIV_I16_CONST_CONST = 87,
    VM_OPCODE_MOD_I16_REG_REG = 88,
    VM_OPCODE_MOD_I16_REG_CONST = 89,
    VM_OPCODE_MOD_I16_CONST_REG = 90,
    VM_OPCODE_MOD_I16_CONST_CONST = 91,
    VM_OPCODE_EQ_I16_REG_REG = 92,
    VM_OPCODE_EQ_I16_REG_CONST = 93,
    VM_OPCODE_EQ_I16_CONST_REG = 94,
    VM_OPCODE_EQ_I16_CONST_CONST = 95,
    VM_OPCODE_LT_I16_REG_REG = 96,
    VM_OPCODE_LT_I16_REG_CONST = 97,
    VM_OPCODE_LT_I16_CONST_REG = 98,
    VM_OPCODE_LT_I16_CONST_CONST = 99,
    VM_OPCODE_BB_I16_REG_REG = 100,
    VM_OPCODE_BB_I16_REG_CONST = 101,
    VM_OPCODE_BB_I16_CONST_REG = 102,
    VM_OPCODE_BB_I16_CONST_CONST = 103,
    VM_OPCODE_BEQ_I16_REG_REG = 104,
    VM_OPCODE_BEQ_I16_REG_CONST = 105,
    VM_OPCODE_BEQ_I16_CONST_REG = 106,
    VM_OPCODE_BEQ_I16_CONST_CONST = 107,
    VM_OPCODE_BLT_I16_REG_REG = 108,
    VM_OPCODE_BLT_I16_REG_CONST = 109,
    VM_OPCODE_BLT_I16_CONST_REG = 110,
    VM_OPCODE_BLT_I16_CONST_CONST = 111,
    VM_OPCODE_MOVE_I16_REG = 112,
    VM_OPCODE_MOVE_I16_CONST = 113,
    VM_OPCODE_OUT_I16_REG = 114,
    VM_OPCODE_OUT_I16_CONST = 115,
    VM_OPCODE_IN_I16_VOID = 116,
    VM_OPCODE_RET_I16_REG = 117,
    VM_OPCODE_RET_I16_CONST = 118,
    VM_OPCODE_TYPE_I16_REG = 119,
    VM_OPCODE_TYPE_I16_CONST = 120,
    VM_OPCODE_BNOT_I16_REG = 121,
    VM_OPCODE_BNOT_I16_CONST = 122,
    VM_OPCODE_BOR_I16_REG_REG = 123,
    VM_OPCODE_BOR_I16_REG_CONST = 124,
    VM_OPCODE_BOR_I16_CONST_REG = 125,
    VM_OPCODE_BOR_I16_CONST_CONST = 126,
    VM_OPCODE_BXOR_I16_REG_REG = 127,
    VM_OPCODE_BXOR_I16_REG_CONST = 128,
    VM_OPCODE_BXOR_I16_CONST_REG = 129,
    VM_OPCODE_BXOR_I16_CONST_CONST = 130,
    VM_OPCODE_BAND_I16_REG_REG = 131,
    VM_OPCODE_BAND_I16_REG_CONST = 132,
    VM_OPCODE_BAND_I16_CONST_REG = 133,
    VM_OPCODE_BAND_I16_CONST_CONST = 134,
    VM_OPCODE_BSHL_I16_REG_REG = 135,
    VM_OPCODE_BSHL_I16_REG_CONST = 136,
    VM_OPCODE_BSHL_I16_CONST_REG = 137,
    VM_OPCODE_BSHL_I16_CONST_CONST = 138,
    VM_OPCODE_BSHR_I16_REG_REG = 139,
    VM_OPCODE_BSHR_I16_REG_CONST = 140,
    VM_OPCODE_BSHR_I16_CONST_REG = 141,
    VM_OPCODE_BSHR_I16_CONST_CONST = 142,
    VM_OPCODE_ADD_I32_REG_REG = 143,
    VM_OPCODE_ADD_I32_REG_CONST = 144,
    VM_OPCODE_ADD_I32_CONST_REG = 145,
    VM_OPCODE_ADD_I32_CONST_CONST = 146,
    VM_OPCODE_SUB_I32_REG_REG = 147,
    VM_OPCODE_SUB_I32_REG_CONST = 148,
    VM_OPCODE_SUB_I32_CONST_REG = 149,
    VM_OPCODE_SUB_I32_CONST_CONST = 150,
    VM_OPCODE_MUL_I32_REG_REG = 151,
    VM_OPCODE_MUL_I32_REG_CONST = 152,
    VM_OPCODE_MUL_I32_CONST_REG = 153,
    VM_OPCODE_MUL_I32_CONST_CONST = 154,
    VM_OPCODE_DIV_I32_REG_REG = 155,
    VM_OPCODE_DIV_I32_REG_CONST = 156,
    VM_OPCODE_DIV_I32_CONST_REG = 157,
    VM_OPCODE_DIV_I32_CONST_CONST = 158,
    VM_OPCODE_MOD_I32_REG_REG = 159,
    VM_OPCODE_MOD_I32_REG_CONST = 160,
    VM_OPCODE_MOD_I32_CONST_REG = 161,
    VM_OPCODE_MOD_I32_CONST_CONST = 162,
    VM_OPCODE_EQ_I32_REG_REG = 163,
    VM_OPCODE_EQ_I32_REG_CONST = 164,
    VM_OPCODE_EQ_I32_CONST_REG = 165,
    VM_OPCODE_EQ_I32_CONST_CONST = 166,
    VM_OPCODE_LT_I32_REG_REG = 167,
    VM_OPCODE_LT_I32_REG_CONST = 168,
    VM_OPCODE_LT_I32_CONST_REG = 169,
    VM_OPCODE_LT_I32_CONST_CONST = 170,
    VM_OPCODE_BB_I32_REG_REG = 171,
    VM_OPCODE_BB_I32_REG_CONST = 172,
    VM_OPCODE_BB_I32_CONST_REG = 173,
    VM_OPCODE_BB_I32_CONST_CONST = 174,
    VM_OPCODE_BEQ_I32_REG_REG = 175,
    VM_OPCODE_BEQ_I32_REG_CONST = 176,
    VM_OPCODE_BEQ_I32_CONST_REG = 177,
    VM_OPCODE_BEQ_I32_CONST_CONST = 178,
    VM_OPCODE_BLT_I32_REG_REG = 179,
    VM_OPCODE_BLT_I32_REG_CONST = 180,
    VM_OPCODE_BLT_I32_CONST_REG = 181,
    VM_OPCODE_BLT_I32_CONST_CONST = 182,
    VM_OPCODE_MOVE_I32_REG = 183,
    VM_OPCODE_MOVE_I32_CONST = 184,
    VM_OPCODE_OUT_I32_REG = 185,
    VM_OPCODE_OUT_I32_CONST = 186,
    VM_OPCODE_IN_I32_VOID = 187,
    VM_OPCODE_RET_I32_REG = 188,
    VM_OPCODE_RET_I32_CONST = 189,
    VM_OPCODE_TYPE_I32_REG = 190,
    VM_OPCODE_TYPE_I32_CONST = 191,
    VM_OPCODE_BNOT_I32_REG = 192,
    VM_OPCODE_BNOT_I32_CONST = 193,
    VM_OPCODE_BOR_I32_REG_REG = 194,
    VM_OPCODE_BOR_I32_REG_CONST = 195,
    VM_OPCODE_BOR_I32_CONST_REG = 196,
    VM_OPCODE_BOR_I32_CONST_CONST = 197,
    VM_OPCODE_BXOR_I32_REG_REG = 198,
    VM_OPCODE_BXOR_I32_REG_CONST = 199,
    VM_OPCODE_BXOR_I32_CONST_REG = 200,
    VM_OPCODE_BXOR_I32_CONST_CONST = 201,
    VM_OPCODE_BAND_I32_REG_REG = 202,
    VM_OPCODE_BAND_I32_REG_CONST = 203,
    VM_OPCODE_BAND_I32_CONST_REG = 204,
    VM_OPCODE_BAND_I32_CONST_CONST = 205,
    VM_OPCODE_BSHL_I32_REG_REG = 206,
    VM_OPCODE_BSHL_I32_REG_CONST = 207,
    VM_OPCODE_BSHL_I32_CONST_REG = 208,
    VM_OPCODE_BSHL_I32_CONST_CONST = 209,
    VM_OPCODE_BSHR_I32_REG_REG = 210,
    VM_OPCODE_BSHR_I32_REG_CONST = 211,
    VM_OPCODE_BSHR_I32_CONST_REG = 212,
    VM_OPCODE_BSHR_I32_CONST_CONST = 213,
    VM_OPCODE_ADD_I64_REG_REG = 214,
    VM_OPCODE_ADD_I64_REG_CONST = 215,
    VM_OPCODE_ADD_I64_CONST_REG = 216,
    VM_OPCODE_ADD_I64_CONST_CONST = 217,
    VM_OPCODE_SUB_I64_REG_REG = 218,
    VM_OPCODE_SUB_I64_REG_CONST = 219,
    VM_OPCODE_SUB_I64_CONST_REG = 220,
    VM_OPCODE_SUB_I64_CONST_CONST = 221,
    VM_OPCODE_MUL_I64_REG_REG = 222,
    VM_OPCODE_MUL_I64_REG_CONST = 223,
    VM_OPCODE_MUL_I64_CONST_REG = 224,
    VM_OPCODE_MUL_I64_CONST_CONST = 225,
    VM_OPCODE_DIV_I64_REG_REG = 226,
    VM_OPCODE_DIV_I64_REG_CONST = 227,
    VM_OPCODE_DIV_I64_CONST_REG = 228,
    VM_OPCODE_DIV_I64_CONST_CONST = 229,
    VM_OPCODE_MOD_I64_REG_REG = 230,
    VM_OPCODE_MOD_I64_REG_CONST = 231,
    VM_OPCODE_MOD_I64_CONST_REG = 232,
    VM_OPCODE_MOD_I64_CONST_CONST = 233,
    VM_OPCODE_EQ_I64_REG_REG = 234,
    VM_OPCODE_EQ_I64_REG_CONST = 235,
    VM_OPCODE_EQ_I64_CONST_REG = 236,
    VM_OPCODE_EQ_I64_CONST_CONST = 237,
    VM_OPCODE_LT_I64_REG_REG = 238,
    VM_OPCODE_LT_I64_REG_CONST = 239,
    VM_OPCODE_LT_I64_CONST_REG = 240,
    VM_OPCODE_LT_I64_CONST_CONST = 241,
    VM_OPCODE_BB_I64_REG_REG = 242,
    VM_OPCODE_BB_I64_REG_CONST = 243,
    VM_OPCODE_BB_I64_CONST_REG = 244,
    VM_OPCODE_BB_I64_CONST_CONST = 245,
    VM_OPCODE_BEQ_I64_REG_REG = 246,
    VM_OPCODE_BEQ_I64_REG_CONST = 247,
    VM_OPCODE_BEQ_I64_CONST_REG = 248,
    VM_OPCODE_BEQ_I64_CONST_CONST = 249,
    VM_OPCODE_BLT_I64_REG_REG = 250,
    VM_OPCODE_BLT_I64_REG_CONST = 251,
    VM_OPCODE_BLT_I64_CONST_REG = 252,
    VM_OPCODE_BLT_I64_CONST_CONST = 253,
    VM_OPCODE_MOVE_I64_REG = 254,
    VM_OPCODE_MOVE_I64_CONST = 255,
    VM_OPCODE_OUT_I64_REG = 256,
    VM_OPCODE_OUT_I64_CONST = 257,
    VM_OPCODE_IN_I64_VOID = 258,
    VM_OPCODE_RET_I64_REG = 259,
    VM_OPCODE_RET_I64_CONST = 260,
    VM_OPCODE_TYPE_I64_REG = 261,
    VM_OPCODE_TYPE_I64_CONST = 262,
    VM_OPCODE_BNOT_I64_REG = 263,
    VM_OPCODE_BNOT_I64_CONST = 264,
    VM_OPCODE_BOR_I64_REG_REG = 265,
    VM_OPCODE_BOR_I64_REG_CONST = 266,
    VM_OPCODE_BOR_I64_CONST_REG = 267,
    VM_OPCODE_BOR_I64_CONST_CONST = 268,
    VM_OPCODE_BXOR_I64_REG_REG = 269,
    VM_OPCODE_BXOR_I64_REG_CONST = 270,
    VM_OPCODE_BXOR_I64_CONST_REG = 271,
    VM_OPCODE_BXOR_I64_CONST_CONST = 272,
    VM_OPCODE_BAND_I64_REG_REG = 273,
    VM_OPCODE_BAND_I64_REG_CONST = 274,
    VM_OPCODE_BAND_I64_CONST_REG = 275,
    VM_OPCODE_BAND_I64_CONST_CONST = 276,
    VM_OPCODE_BSHL_I64_REG_REG = 277,
    VM_OPCODE_BSHL_I64_REG_CONST = 278,
    VM_OPCODE_BSHL_I64_CONST_REG = 279,
    VM_OPCODE_BSHL_I64_CONST_CONST = 280,
    VM_OPCODE_BSHR_I64_REG_REG = 281,
    VM_OPCODE_BSHR_I64_REG_CONST = 282,
    VM_OPCODE_BSHR_I64_CONST_REG = 283,
    VM_OPCODE_BSHR_I64_CONST_CONST = 284,
    VM_OPCODE_ADD_U8_REG_REG = 285,
    VM_OPCODE_ADD_U8_REG_CONST = 286,
    VM_OPCODE_ADD_U8_CONST_REG = 287,
    VM_OPCODE_ADD_U8_CONST_CONST = 288,
    VM_OPCODE_SUB_U8_REG_REG = 289,
    VM_OPCODE_SUB_U8_REG_CONST = 290,
    VM_OPCODE_SUB_U8_CONST_REG = 291,
    VM_OPCODE_SUB_U8_CONST_CONST = 292,
    VM_OPCODE_MUL_U8_REG_REG = 293,
    VM_OPCODE_MUL_U8_REG_CONST = 294,
    VM_OPCODE_MUL_U8_CONST_REG = 295,
    VM_OPCODE_MUL_U8_CONST_CONST = 296,
    VM_OPCODE_DIV_U8_REG_REG = 297,
    VM_OPCODE_DIV_U8_REG_CONST = 298,
    VM_OPCODE_DIV_U8_CONST_REG = 299,
    VM_OPCODE_DIV_U8_CONST_CONST = 300,
    VM_OPCODE_MOD_U8_REG_REG = 301,
    VM_OPCODE_MOD_U8_REG_CONST = 302,
    VM_OPCODE_MOD_U8_CONST_REG = 303,
    VM_OPCODE_MOD_U8_CONST_CONST = 304,
    VM_OPCODE_EQ_U8_REG_REG = 305,
    VM_OPCODE_EQ_U8_REG_CONST = 306,
    VM_OPCODE_EQ_U8_CONST_REG = 307,
    VM_OPCODE_EQ_U8_CONST_CONST = 308,
    VM_OPCODE_LT_U8_REG_REG = 309,
    VM_OPCODE_LT_U8_REG_CONST = 310,
    VM_OPCODE_LT_U8_CONST_REG = 311,
    VM_OPCODE_LT_U8_CONST_CONST = 312,
    VM_OPCODE_BB_U8_REG_REG = 313,
    VM_OPCODE_BB_U8_REG_CONST = 314,
    VM_OPCODE_BB_U8_CONST_REG = 315,
    VM_OPCODE_BB_U8_CONST_CONST = 316,
    VM_OPCODE_BEQ_U8_REG_REG = 317,
    VM_OPCODE_BEQ_U8_REG_CONST = 318,
    VM_OPCODE_BEQ_U8_CONST_REG = 319,
    VM_OPCODE_BEQ_U8_CONST_CONST = 320,
    VM_OPCODE_BLT_U8_REG_REG = 321,
    VM_OPCODE_BLT_U8_REG_CONST = 322,
    VM_OPCODE_BLT_U8_CONST_REG = 323,
    VM_OPCODE_BLT_U8_CONST_CONST = 324,
    VM_OPCODE_MOVE_U8_REG = 325,
    VM_OPCODE_MOVE_U8_CONST = 326,
    VM_OPCODE_OUT_U8_REG = 327,
    VM_OPCODE_OUT_U8_CONST = 328,
    VM_OPCODE_IN_U8_VOID = 329,
    VM_OPCODE_RET_U8_REG = 330,
    VM_OPCODE_RET_U8_CONST = 331,
    VM_OPCODE_TYPE_U8_REG = 332,
    VM_OPCODE_TYPE_U8_CONST = 333,
    VM_OPCODE_BNOT_U8_REG = 334,
    VM_OPCODE_BNOT_U8_CONST = 335,
    VM_OPCODE_BOR_U8_REG_REG = 336,
    VM_OPCODE_BOR_U8_REG_CONST = 337,
    VM_OPCODE_BOR_U8_CONST_REG = 338,
    VM_OPCODE_BOR_U8_CONST_CONST = 339,
    VM_OPCODE_BXOR_U8_REG_REG = 340,
    VM_OPCODE_BXOR_U8_REG_CONST = 341,
    VM_OPCODE_BXOR_U8_CONST_REG = 342,
    VM_OPCODE_BXOR_U8_CONST_CONST = 343,
    VM_OPCODE_BAND_U8_REG_REG = 344,
    VM_OPCODE_BAND_U8_REG_CONST = 345,
    VM_OPCODE_BAND_U8_CONST_REG = 346,
    VM_OPCODE_BAND_U8_CONST_CONST = 347,
    VM_OPCODE_BSHL_U8_REG_REG = 348,
    VM_OPCODE_BSHL_U8_REG_CONST = 349,
    VM_OPCODE_BSHL_U8_CONST_REG = 350,
    VM_OPCODE_BSHL_U8_CONST_CONST = 351,
    VM_OPCODE_BSHR_U8_REG_REG = 352,
    VM_OPCODE_BSHR_U8_REG_CONST = 353,
    VM_OPCODE_BSHR_U8_CONST_REG = 354,
    VM_OPCODE_BSHR_U8_CONST_CONST = 355,
    VM_OPCODE_ADD_U16_REG_REG = 356,
    VM_OPCODE_ADD_U16_REG_CONST = 357,
    VM_OPCODE_ADD_U16_CONST_REG = 358,
    VM_OPCODE_ADD_U16_CONST_CONST = 359,
    VM_OPCODE_SUB_U16_REG_REG = 360,
    VM_OPCODE_SUB_U16_REG_CONST = 361,
    VM_OPCODE_SUB_U16_CONST_REG = 362,
    VM_OPCODE_SUB_U16_CONST_CONST = 363,
    VM_OPCODE_MUL_U16_REG_REG = 364,
    VM_OPCODE_MUL_U16_REG_CONST = 365,
    VM_OPCODE_MUL_U16_CONST_REG = 366,
    VM_OPCODE_MUL_U16_CONST_CONST = 367,
    VM_OPCODE_DIV_U16_REG_REG = 368,
    VM_OPCODE_DIV_U16_REG_CONST = 369,
    VM_OPCODE_DIV_U16_CONST_REG = 370,
    VM_OPCODE_DIV_U16_CONST_CONST = 371,
    VM_OPCODE_MOD_U16_REG_REG = 372,
    VM_OPCODE_MOD_U16_REG_CONST = 373,
    VM_OPCODE_MOD_U16_CONST_REG = 374,
    VM_OPCODE_MOD_U16_CONST_CONST = 375,
    VM_OPCODE_EQ_U16_REG_REG = 376,
    VM_OPCODE_EQ_U16_REG_CONST = 377,
    VM_OPCODE_EQ_U16_CONST_REG = 378,
    VM_OPCODE_EQ_U16_CONST_CONST = 379,
    VM_OPCODE_LT_U16_REG_REG = 380,
    VM_OPCODE_LT_U16_REG_CONST = 381,
    VM_OPCODE_LT_U16_CONST_REG = 382,
    VM_OPCODE_LT_U16_CONST_CONST = 383,
    VM_OPCODE_BB_U16_REG_REG = 384,
    VM_OPCODE_BB_U16_REG_CONST = 385,
    VM_OPCODE_BB_U16_CONST_REG = 386,
    VM_OPCODE_BB_U16_CONST_CONST = 387,
    VM_OPCODE_BEQ_U16_REG_REG = 388,
    VM_OPCODE_BEQ_U16_REG_CONST = 389,
    VM_OPCODE_BEQ_U16_CONST_REG = 390,
    VM_OPCODE_BEQ_U16_CONST_CONST = 391,
    VM_OPCODE_BLT_U16_REG_REG = 392,
    VM_OPCODE_BLT_U16_REG_CONST = 393,
    VM_OPCODE_BLT_U16_CONST_REG = 394,
    VM_OPCODE_BLT_U16_CONST_CONST = 395,
    VM_OPCODE_MOVE_U16_REG = 396,
    VM_OPCODE_MOVE_U16_CONST = 397,
    VM_OPCODE_OUT_U16_REG = 398,
    VM_OPCODE_OUT_U16_CONST = 399,
    VM_OPCODE_IN_U16_VOID = 400,
    VM_OPCODE_RET_U16_REG = 401,
    VM_OPCODE_RET_U16_CONST = 402,
    VM_OPCODE_TYPE_U16_REG = 403,
    VM_OPCODE_TYPE_U16_CONST = 404,
    VM_OPCODE_BNOT_U16_REG = 405,
    VM_OPCODE_BNOT_U16_CONST = 406,
    VM_OPCODE_BOR_U16_REG_REG = 407,
    VM_OPCODE_BOR_U16_REG_CONST = 408,
    VM_OPCODE_BOR_U16_CONST_REG = 409,
    VM_OPCODE_BOR_U16_CONST_CONST = 410,
    VM_OPCODE_BXOR_U16_REG_REG = 411,
    VM_OPCODE_BXOR_U16_REG_CONST = 412,
    VM_OPCODE_BXOR_U16_CONST_REG = 413,
    VM_OPCODE_BXOR_U16_CONST_CONST = 414,
    VM_OPCODE_BAND_U16_REG_REG = 415,
    VM_OPCODE_BAND_U16_REG_CONST = 416,
    VM_OPCODE_BAND_U16_CONST_REG = 417,
    VM_OPCODE_BAND_U16_CONST_CONST = 418,
    VM_OPCODE_BSHL_U16_REG_REG = 419,
    VM_OPCODE_BSHL_U16_REG_CONST = 420,
    VM_OPCODE_BSHL_U16_CONST_REG = 421,
    VM_OPCODE_BSHL_U16_CONST_CONST = 422,
    VM_OPCODE_BSHR_U16_REG_REG = 423,
    VM_OPCODE_BSHR_U16_REG_CONST = 424,
    VM_OPCODE_BSHR_U16_CONST_REG = 425,
    VM_OPCODE_BSHR_U16_CONST_CONST = 426,
    VM_OPCODE_ADD_U32_REG_REG = 427,
    VM_OPCODE_ADD_U32_REG_CONST = 428,
    VM_OPCODE_ADD_U32_CONST_REG = 429,
    VM_OPCODE_ADD_U32_CONST_CONST = 430,
    VM_OPCODE_SUB_U32_REG_REG = 431,
    VM_OPCODE_SUB_U32_REG_CONST = 432,
    VM_OPCODE_SUB_U32_CONST_REG = 433,
    VM_OPCODE_SUB_U32_CONST_CONST = 434,
    VM_OPCODE_MUL_U32_REG_REG = 435,
    VM_OPCODE_MUL_U32_REG_CONST = 436,
    VM_OPCODE_MUL_U32_CONST_REG = 437,
    VM_OPCODE_MUL_U32_CONST_CONST = 438,
    VM_OPCODE_DIV_U32_REG_REG = 439,
    VM_OPCODE_DIV_U32_REG_CONST = 440,
    VM_OPCODE_DIV_U32_CONST_REG = 441,
    VM_OPCODE_DIV_U32_CONST_CONST = 442,
    VM_OPCODE_MOD_U32_REG_REG = 443,
    VM_OPCODE_MOD_U32_REG_CONST = 444,
    VM_OPCODE_MOD_U32_CONST_REG = 445,
    VM_OPCODE_MOD_U32_CONST_CONST = 446,
    VM_OPCODE_EQ_U32_REG_REG = 447,
    VM_OPCODE_EQ_U32_REG_CONST = 448,
    VM_OPCODE_EQ_U32_CONST_REG = 449,
    VM_OPCODE_EQ_U32_CONST_CONST = 450,
    VM_OPCODE_LT_U32_REG_REG = 451,
    VM_OPCODE_LT_U32_REG_CONST = 452,
    VM_OPCODE_LT_U32_CONST_REG = 453,
    VM_OPCODE_LT_U32_CONST_CONST = 454,
    VM_OPCODE_BB_U32_REG_REG = 455,
    VM_OPCODE_BB_U32_REG_CONST = 456,
    VM_OPCODE_BB_U32_CONST_REG = 457,
    VM_OPCODE_BB_U32_CONST_CONST = 458,
    VM_OPCODE_BEQ_U32_REG_REG = 459,
    VM_OPCODE_BEQ_U32_REG_CONST = 460,
    VM_OPCODE_BEQ_U32_CONST_REG = 461,
    VM_OPCODE_BEQ_U32_CONST_CONST = 462,
    VM_OPCODE_BLT_U32_REG_REG = 463,
    VM_OPCODE_BLT_U32_REG_CONST = 464,
    VM_OPCODE_BLT_U32_CONST_REG = 465,
    VM_OPCODE_BLT_U32_CONST_CONST = 466,
    VM_OPCODE_MOVE_U32_REG = 467,
    VM_OPCODE_MOVE_U32_CONST = 468,
    VM_OPCODE_OUT_U32_REG = 469,
    VM_OPCODE_OUT_U32_CONST = 470,
    VM_OPCODE_IN_U32_VOID = 471,
    VM_OPCODE_RET_U32_REG = 472,
    VM_OPCODE_RET_U32_CONST = 473,
    VM_OPCODE_TYPE_U32_REG = 474,
    VM_OPCODE_TYPE_U32_CONST = 475,
    VM_OPCODE_BNOT_U32_REG = 476,
    VM_OPCODE_BNOT_U32_CONST = 477,
    VM_OPCODE_BOR_U32_REG_REG = 478,
    VM_OPCODE_BOR_U32_REG_CONST = 479,
    VM_OPCODE_BOR_U32_CONST_REG = 480,
    VM_OPCODE_BOR_U32_CONST_CONST = 481,
    VM_OPCODE_BXOR_U32_REG_REG = 482,
    VM_OPCODE_BXOR_U32_REG_CONST = 483,
    VM_OPCODE_BXOR_U32_CONST_REG = 484,
    VM_OPCODE_BXOR_U32_CONST_CONST = 485,
    VM_OPCODE_BAND_U32_REG_REG = 486,
    VM_OPCODE_BAND_U32_REG_CONST = 487,
    VM_OPCODE_BAND_U32_CONST_REG = 488,
    VM_OPCODE_BAND_U32_CONST_CONST = 489,
    VM_OPCODE_BSHL_U32_REG_REG = 490,
    VM_OPCODE_BSHL_U32_REG_CONST = 491,
    VM_OPCODE_BSHL_U32_CONST_REG = 492,
    VM_OPCODE_BSHL_U32_CONST_CONST = 493,
    VM_OPCODE_BSHR_U32_REG_REG = 494,
    VM_OPCODE_BSHR_U32_REG_CONST = 495,
    VM_OPCODE_BSHR_U32_CONST_REG = 496,
    VM_OPCODE_BSHR_U32_CONST_CONST = 497,
    VM_OPCODE_ADD_U64_REG_REG = 498,
    VM_OPCODE_ADD_U64_REG_CONST = 499,
    VM_OPCODE_ADD_U64_CONST_REG = 500,
    VM_OPCODE_ADD_U64_CONST_CONST = 501,
    VM_OPCODE_SUB_U64_REG_REG = 502,
    VM_OPCODE_SUB_U64_REG_CONST = 503,
    VM_OPCODE_SUB_U64_CONST_REG = 504,
    VM_OPCODE_SUB_U64_CONST_CONST = 505,
    VM_OPCODE_MUL_U64_REG_REG = 506,
    VM_OPCODE_MUL_U64_REG_CONST = 507,
    VM_OPCODE_MUL_U64_CONST_REG = 508,
    VM_OPCODE_MUL_U64_CONST_CONST = 509,
    VM_OPCODE_DIV_U64_REG_REG = 510,
    VM_OPCODE_DIV_U64_REG_CONST = 511,
    VM_OPCODE_DIV_U64_CONST_REG = 512,
    VM_OPCODE_DIV_U64_CONST_CONST = 513,
    VM_OPCODE_MOD_U64_REG_REG = 514,
    VM_OPCODE_MOD_U64_REG_CONST = 515,
    VM_OPCODE_MOD_U64_CONST_REG = 516,
    VM_OPCODE_MOD_U64_CONST_CONST = 517,
    VM_OPCODE_EQ_U64_REG_REG = 518,
    VM_OPCODE_EQ_U64_REG_CONST = 519,
    VM_OPCODE_EQ_U64_CONST_REG = 520,
    VM_OPCODE_EQ_U64_CONST_CONST = 521,
    VM_OPCODE_LT_U64_REG_REG = 522,
    VM_OPCODE_LT_U64_REG_CONST = 523,
    VM_OPCODE_LT_U64_CONST_REG = 524,
    VM_OPCODE_LT_U64_CONST_CONST = 525,
    VM_OPCODE_BB_U64_REG_REG = 526,
    VM_OPCODE_BB_U64_REG_CONST = 527,
    VM_OPCODE_BB_U64_CONST_REG = 528,
    VM_OPCODE_BB_U64_CONST_CONST = 529,
    VM_OPCODE_BEQ_U64_REG_REG = 530,
    VM_OPCODE_BEQ_U64_REG_CONST = 531,
    VM_OPCODE_BEQ_U64_CONST_REG = 532,
    VM_OPCODE_BEQ_U64_CONST_CONST = 533,
    VM_OPCODE_BLT_U64_REG_REG = 534,
    VM_OPCODE_BLT_U64_REG_CONST = 535,
    VM_OPCODE_BLT_U64_CONST_REG = 536,
    VM_OPCODE_BLT_U64_CONST_CONST = 537,
    VM_OPCODE_MOVE_U64_REG = 538,
    VM_OPCODE_MOVE_U64_CONST = 539,
    VM_OPCODE_OUT_U64_REG = 540,
    VM_OPCODE_OUT_U64_CONST = 541,
    VM_OPCODE_IN_U64_VOID = 542,
    VM_OPCODE_RET_U64_REG = 543,
    VM_OPCODE_RET_U64_CONST = 544,
    VM_OPCODE_TYPE_U64_REG = 545,
    VM_OPCODE_TYPE_U64_CONST = 546,
    VM_OPCODE_BNOT_U64_REG = 547,
    VM_OPCODE_BNOT_U64_CONST = 548,
    VM_OPCODE_BOR_U64_REG_REG = 549,
    VM_OPCODE_BOR_U64_REG_CONST = 550,
    VM_OPCODE_BOR_U64_CONST_REG = 551,
    VM_OPCODE_BOR_U64_CONST_CONST = 552,
    VM_OPCODE_BXOR_U64_REG_REG = 553,
    VM_OPCODE_BXOR_U64_REG_CONST = 554,
    VM_OPCODE_BXOR_U64_CONST_REG = 555,
    VM_OPCODE_BXOR_U64_CONST_CONST = 556,
    VM_OPCODE_BAND_U64_REG_REG = 557,
    VM_OPCODE_BAND_U64_REG_CONST = 558,
    VM_OPCODE_BAND_U64_CONST_REG = 559,
    VM_OPCODE_BAND_U64_CONST_CONST = 560,
    VM_OPCODE_BSHL_U64_REG_REG = 561,
    VM_OPCODE_BSHL_U64_REG_CONST = 562,
    VM_OPCODE_BSHL_U64_CONST_REG = 563,
    VM_OPCODE_BSHL_U64_CONST_CONST = 564,
    VM_OPCODE_BSHR_U64_REG_REG = 565,
    VM_OPCODE_BSHR_U64_REG_CONST = 566,
    VM_OPCODE_BSHR_U64_CONST_REG = 567,
    VM_OPCODE_BSHR_U64_CONST_CONST = 568,
    VM_OPCODE_ADD_F32_REG_REG = 569,
    VM_OPCODE_ADD_F32_REG_CONST = 570,
    VM_OPCODE_ADD_F32_CONST_REG = 571,
    VM_OPCODE_ADD_F32_CONST_CONST = 572,
    VM_OPCODE_SUB_F32_REG_REG = 573,
    VM_OPCODE_SUB_F32_REG_CONST = 574,
    VM_OPCODE_SUB_F32_CONST_REG = 575,
    VM_OPCODE_SUB_F32_CONST_CONST = 576,
    VM_OPCODE_MUL_F32_REG_REG = 577,
    VM_OPCODE_MUL_F32_REG_CONST = 578,
    VM_OPCODE_MUL_F32_CONST_REG = 579,
    VM_OPCODE_MUL_F32_CONST_CONST = 580,
    VM_OPCODE_DIV_F32_REG_REG = 581,
    VM_OPCODE_DIV_F32_REG_CONST = 582,
    VM_OPCODE_DIV_F32_CONST_REG = 583,
    VM_OPCODE_DIV_F32_CONST_CONST = 584,
    VM_OPCODE_MOD_F32_REG_REG = 585,
    VM_OPCODE_MOD_F32_REG_CONST = 586,
    VM_OPCODE_MOD_F32_CONST_REG = 587,
    VM_OPCODE_MOD_F32_CONST_CONST = 588,
    VM_OPCODE_EQ_F32_REG_REG = 589,
    VM_OPCODE_EQ_F32_REG_CONST = 590,
    VM_OPCODE_EQ_F32_CONST_REG = 591,
    VM_OPCODE_EQ_F32_CONST_CONST = 592,
    VM_OPCODE_LT_F32_REG_REG = 593,
    VM_OPCODE_LT_F32_REG_CONST = 594,
    VM_OPCODE_LT_F32_CONST_REG = 595,
    VM_OPCODE_LT_F32_CONST_CONST = 596,
    VM_OPCODE_BB_F32_REG_REG = 597,
    VM_OPCODE_BB_F32_REG_CONST = 598,
    VM_OPCODE_BB_F32_CONST_REG = 599,
    VM_OPCODE_BB_F32_CONST_CONST = 600,
    VM_OPCODE_BEQ_F32_REG_REG = 601,
    VM_OPCODE_BEQ_F32_REG_CONST = 602,
    VM_OPCODE_BEQ_F32_CONST_REG = 603,
    VM_OPCODE_BEQ_F32_CONST_CONST = 604,
    VM_OPCODE_BLT_F32_REG_REG = 605,
    VM_OPCODE_BLT_F32_REG_CONST = 606,
    VM_OPCODE_BLT_F32_CONST_REG = 607,
    VM_OPCODE_BLT_F32_CONST_CONST = 608,
    VM_OPCODE_MOVE_F32_REG = 609,
    VM_OPCODE_MOVE_F32_CONST = 610,
    VM_OPCODE_OUT_F32_REG = 611,
    VM_OPCODE_OUT_F32_CONST = 612,
    VM_OPCODE_IN_F32_VOID = 613,
    VM_OPCODE_RET_F32_REG = 614,
    VM_OPCODE_RET_F32_CONST = 615,
    VM_OPCODE_TYPE_F32_REG = 616,
    VM_OPCODE_TYPE_F32_CONST = 617,
    VM_OPCODE_BNOT_F32_REG = 618,
    VM_OPCODE_BNOT_F32_CONST = 619,
    VM_OPCODE_ADD_F64_REG_REG = 620,
    VM_OPCODE_ADD_F64_REG_CONST = 621,
    VM_OPCODE_ADD_F64_CONST_REG = 622,
    VM_OPCODE_ADD_F64_CONST_CONST = 623,
    VM_OPCODE_SUB_F64_REG_REG = 624,
    VM_OPCODE_SUB_F64_REG_CONST = 625,
    VM_OPCODE_SUB_F64_CONST_REG = 626,
    VM_OPCODE_SUB_F64_CONST_CONST = 627,
    VM_OPCODE_MUL_F64_REG_REG = 628,
    VM_OPCODE_MUL_F64_REG_CONST = 629,
    VM_OPCODE_MUL_F64_CONST_REG = 630,
    VM_OPCODE_MUL_F64_CONST_CONST = 631,
    VM_OPCODE_DIV_F64_REG_REG = 632,
    VM_OPCODE_DIV_F64_REG_CONST = 633,
    VM_OPCODE_DIV_F64_CONST_REG = 634,
    VM_OPCODE_DIV_F64_CONST_CONST = 635,
    VM_OPCODE_MOD_F64_REG_REG = 636,
    VM_OPCODE_MOD_F64_REG_CONST = 637,
    VM_OPCODE_MOD_F64_CONST_REG = 638,
    VM_OPCODE_MOD_F64_CONST_CONST = 639,
    VM_OPCODE_EQ_F64_REG_REG = 640,
    VM_OPCODE_EQ_F64_REG_CONST = 641,
    VM_OPCODE_EQ_F64_CONST_REG = 642,
    VM_OPCODE_EQ_F64_CONST_CONST = 643,
    VM_OPCODE_LT_F64_REG_REG = 644,
    VM_OPCODE_LT_F64_REG_CONST = 645,
    VM_OPCODE_LT_F64_CONST_REG = 646,
    VM_OPCODE_LT_F64_CONST_CONST = 647,
    VM_OPCODE_BB_F64_REG_REG = 648,
    VM_OPCODE_BB_F64_REG_CONST = 649,
    VM_OPCODE_BB_F64_CONST_REG = 650,
    VM_OPCODE_BB_F64_CONST_CONST = 651,
    VM_OPCODE_BEQ_F64_REG_REG = 652,
    VM_OPCODE_BEQ_F64_REG_CONST = 653,
    VM_OPCODE_BEQ_F64_CONST_REG = 654,
    VM_OPCODE_BEQ_F64_CONST_CONST = 655,
    VM_OPCODE_BLT_F64_REG_REG = 656,
    VM_OPCODE_BLT_F64_REG_CONST = 657,
    VM_OPCODE_BLT_F64_CONST_REG = 658,
    VM_OPCODE_BLT_F64_CONST_CONST = 659,
    VM_OPCODE_MOVE_F64_REG = 660,
    VM_OPCODE_MOVE_F64_CONST = 661,
    VM_OPCODE_OUT_F64_REG = 662,
    VM_OPCODE_OUT_F64_CONST = 663,
    VM_OPCODE_IN_F64_VOID = 664,
    VM_OPCODE_RET_F64_REG = 665,
    VM_OPCODE_RET_F64_CONST = 666,
    VM_OPCODE_TYPE_F64_REG = 667,
    VM_OPCODE_TYPE_F64_CONST = 668,
    VM_OPCODE_BNOT_F64_REG = 669,
    VM_OPCODE_BNOT_F64_CONST = 670,
    VM_OPCODE_CALL_FUNC_CONST = 671,
    VM_OPCODE_CALL_FUNC_REG = 672,
    VM_OPCODE_CALL_FUNC_CONST_REG = 673,
    VM_OPCODE_CALL_FUNC_REG_REG = 674,
    VM_OPCODE_CALL_FUNC_CONST_REG_REG = 675,
    VM_OPCODE_CALL_FUNC_REG_REG_REG = 676,
    VM_OPCODE_CALL_FUNC_CONST_REG_REG_REG = 677,
    VM_OPCODE_CALL_FUNC_REG_REG_REG_REG = 678,
    VM_OPCODE_CALL_FUNC_CONST_REG_REG_REG_REG = 679,
    VM_OPCODE_CALL_FUNC_REG_REG_REG_REG_REG = 680,
    VM_OPCODE_CALL_FUNC_CONST_REG_REG_REG_REG_REG = 681,
    VM_OPCODE_CALL_FUNC_REG_REG_REG_REG_REG_REG = 682,
    VM_OPCODE_CALL_FUNC_CONST_REG_REG_REG_REG_REG_REG = 683,
    VM_OPCODE_CALL_FUNC_REG_REG_REG_REG_REG_REG_REG = 684,
    VM_OPCODE_CALL_FUNC_CONST_REG_REG_REG_REG_REG_REG_REG = 685,
    VM_OPCODE_CALL_FUNC_REG_REG_REG_REG_REG_REG_REG_REG = 686,
    VM_OPCODE_CALL_FUNC_CONST_REG_REG_REG_REG_REG_REG_REG_REG = 687,
    VM_OPCODE_CALL_FUNC_REG_REG_REG_REG_REG_REG_REG_REG_REG = 688
};
struct vm_state_t;
typedef struct vm_state_t vm_state_t;

union vm_opcode_t;
typedef union vm_opcode_t vm_opcode_t;

union vm_opcode_t {
    void *ptr;
    size_t reg;
    int8_t i8;
    int16_t i16;
    int32_t i32;
    int64_t i64;
    uint8_t u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;
    float f32;
    double f64;
    vm_block_t *func;
};

struct vm_state_t {
    vm_opcode_t *head;
    size_t framesize;
    size_t nlocals;
    void *locals;
    void **ptrs;
};

vm_state_t *vm_state_init(size_t nregs);
void vm_state_deinit(vm_state_t *state);
void vm_run(vm_state_t *state, vm_block_t *block);

#endif
