#ifndef REGISTER_TYPES_H
#define REGISTER_TYPES_H
#include <systemc.h>
#define NUMBER_OF_REGISTERS 32

typedef struct {
    int SEW;
    float LMUL;
    char TA;
    char MA;
} Vtype;

typedef struct {
    char* Register0;
    int* Register[NUMBER_OF_REGISTERS-1];
    int VLEN;
    int AVL;
    int VL;
    int VLMAX;
    Vtype vtype;
} Register_Status;

extern Register_Status* reg_status;
extern sc_bv<32>* memory;
extern int INSTRUCTION_MEMORY_SIZE;

#endif
