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

typedef struct{
    uint32_t Scalar_Regiaters[NUMBER_OF_REGISTERS];   // storing raw 32-bits 
    int8_t *Vector_Register0;                         // Vector Register0
    int *Vector_Register [NUMBER_OF_REGISTERS-1];     // Array of vector_Registers (from V1 -> V31 )
    int VLEN;                                         // Length for each Vector register
    int AVL;                                          // AVL (Application vector length)
    uint32_t VL;                                      // Vl (number of elements to process)
    uint32_t VLMAX;                                   // VLAMX = (VLEN/SEW *LMUL )
    Vtype vtype;
} Register_Status;

extern Register_Status* reg_status;
extern sc_bv<32>* memory;
extern int INSTRUCTION_MEMORY_SIZE;

#endif
