#include "include/instructions.h"


///////*                                       INSTRUCTION FUNCTIONS                                      *//////

void vadd_vv(Register_Status * register_status, uint8_t vd, uint8_t vs1, uint8_t vs2,uint8_t vm) {     //VADD_VV
    if(vm==1){
        for (uint64_t i = 0; i < register_status->VL; i++) {
            register_status->Register[vd - 1][i] = 
            register_status->Register[vs1 - 1][i] + register_status->Register[vs2 - 1][i];
        }
    }
    else{}
}

void vadd_vi(Register_Status * register_status, uint8_t vd, uint8_t vs2,int8_t Imm,uint8_t vm) {        //VADD_VI
    if(vm==1){   
        for (uint64_t i = 0; i < register_status->VL; i++) {
            register_status->Register[vd - 1][i] = register_status->Register[vs2 - 1][i] + Imm;
        }
    }
    else{}
    }

  


void vsub_vv(Register_Status * register_status, uint8_t vd, uint8_t vs1, uint8_t vs2,uint8_t vm) {      //VSUB_VV
    if(vm==1){
        for (uint64_t i = 0; i < register_status->VL; i++) {
            register_status->Register[vd - 1][i] = 
            register_status->Register[vs2 - 1][i] - register_status->Register[vs1 - 1][i];
        }
    }
    else{}
}


void vrsub_vi(Register_Status * register_status, uint8_t vd, uint8_t vs2,int8_t Imm,uint8_t vm) {        //Vrsub_VI
    if(vm==1){   
        for (uint64_t i = 0; i < register_status->VL; i++) {
            register_status->Register[vd - 1][i] = Imm - register_status->Register[vs2 - 1][i] ;
        }
    }
    else{}
    }


void vand_vv(Register_Status * register_status, uint8_t vd, uint8_t vs1, uint8_t vs2,uint8_t vm) {      //VAND_VV
    if(vm==1){
           for (uint64_t i = 0; i < register_status->VL; i++) {
              register_status->Register[vd - 1][i] = 
              register_status->Register[vs2 - 1][i] & register_status->Register[vs1 - 1][i];
            }
        }
    else{}
    }

    void vor_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {
        // VOR_VV: Perform bitwise OR between vector registers vs1 and vs2, and store in vd
        if (vm == 1) {
            for (uint64_t i = 0; i < register_status->VL; i++) {
                // Perform bitwise OR operation for each element in the vector
                register_status->Register[vd - 1][i] = 
                    register_status->Register[vs2 - 1][i] | register_status->Register[vs1 - 1][i];
            }
        } else {
            // Handle the case when vm is not equal to 1
        }
    }
    void vxor_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {
        // VXOR_VV: Perform bitwise XOR between vector registers vs1 and vs2, and store in vd
        if (vm == 1) {
            for (uint64_t i = 0; i < register_status->VL; i++) {
                // Perform bitwise XOR operation for each element in the vector
                register_status->Register[vd - 1][i] = 
                    register_status->Register[vs2 - 1][i] ^ register_status->Register[vs1 - 1][i];
            }
        } else {
            // Handle the case when vm is not equal to 1 (optional, depending on the operation definition)
            // This could be where you handle vector masking, depending on the specific behavior.
        }
    }