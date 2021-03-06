// XXX This file is processed by generate_py.py. Avoid changing the format
//     unless you want to generate the ctypes struct yourself. You have been
//     warned!
//
//     In general, adding C++ comments and members in the insn_t should work
//     as expected.
//
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

#ifdef _WIN32
#define EXPORT __declspec(dllexport) extern
#else
#define EXPORT extern
#endif

// Enum of instructions
enum {
    Iinvalid = 0,
#define INS(ins, opcode) I##ins,
#include "opcodes.h"
    I__count
};

// Define a field and its used flag
#define DEFINE_FIELD(type, name) type name; uint8_t used_##name;
// Nameless union wrapper around fields
#define BEGIN_FIELDS() union { struct {
#define END_FIELDS() }; char _fields[1]; };

// Decoded instruction
typedef struct {
    // Structure size (used as sanity check)
    unsigned int _st_size;

    // TODO Instruction
    uint64_t insn;
    // TODO EIP/PC/EA
    uint32_t pc;
    // Input bytes
    const uint16_t *bytes;

    // Instruction size
    unsigned int size;
    // Internal instruction
    unsigned int id;
    // Mnemonic
    const char *mnemonic;
    // Assembly string
    char str[64];

    BEGIN_FIELDS()

    // TODO Decoded fields (must come at the end of struct)
    DEFINE_FIELD(uint32_t, opcode)
    DEFINE_FIELD(uint8_t, rA)
    DEFINE_FIELD(uint8_t, rB)
    DEFINE_FIELD(uint8_t, rC)
    DEFINE_FIELD(uint8_t, arith_signed)
    DEFINE_FIELD(uint8_t, is_imm)
    DEFINE_FIELD(uint32_t, funct)
    DEFINE_FIELD(uint8_t, uf)
    DEFINE_FIELD(uint16_t, reg_count)
    DEFINE_FIELD(uint16_t, cc)
    DEFINE_FIELD(int32_t, imm) // sign-extended
    DEFINE_FIELD(uint8_t, adj_rb)
    DEFINE_FIELD(uint8_t, rw)
    DEFINE_FIELD(uint8_t, mem_flags)

    END_FIELDS()
} inst_t;

EXPORT void disassemble(inst_t *inst, uint32_t pc, const uint16_t *buf);
EXPORT const char *mnemonics[];
EXPORT const char *registers[];
EXPORT const unsigned int num_registers;
#ifdef __cplusplus
}
#endif
