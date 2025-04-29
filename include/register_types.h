#ifndef REGISTER_TYPES_H
#define REGISTER_TYPES_H
#include <systemc.h>

#define NUMBER_OF_REGISTERS 32
#define VLEN 64
 
typedef struct {
    int SEW;
    float LMUL;
    char TA;
    char MA;
    sc_bit vill;
} Vtype;

typedef struct{
    sc_bv<32> Scalar_Registers[NUMBER_OF_REGISTERS];     // storing raw 32-bits (Scalar registers)
    sc_bv<VLEN> Vector_Register[NUMBER_OF_REGISTERS];    // Array of vector_Registers (from V0 -> V31 )                                       // Length for each Vector register
    int AVL;                                             // AVL (Application vector length)
    uint32_t VL;                                         // Vl (number of elements to process)
    uint32_t VLMAX;                                      // VLAMX = (VLEN/SEW *LMUL )
    uint32_t vlenb;                                      // vector register length in bytes
    sc_bv<32> vcsr;                                      //bit[0] = vxsat ( Saturation Flag) , bit[2:1] = vxrm[1:0] (Fixed-Point Rounding Mode)
    Vtype vtype;
} Register_Status;

extern Register_Status* reg_status;

#endif
