#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "register_types.h"

void vadd_vv(Register_Status* register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm);
void vadd_vi(Register_Status* register_status, uint8_t vd, uint8_t vs2, int8_t Imm, uint8_t vm);
void vsub_vv(Register_Status* register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm);
void vrsub_vi(Register_Status* register_status, uint8_t vd, uint8_t vs2, int8_t Imm, uint8_t vm);
void vand_vv(Register_Status* register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm);
void vor_vv(Register_Status* register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm);
void vxor_vv(Register_Status* register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm);
void vxor_vi(Register_Status * register_status, uint8_t vd, uint8_t vs2,int8_t Imm,uint8_t vm);
void vmv_v_v(Register_Status * register_status , uint8_t vd , uint8_t vs1 , uint8_t vm);
void vmv_v_i(Register_Status * register_status , uint8_t vd , int8_t Imm , uint8_t vm);
void vmin_vv(Register_Status* register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm);
void vmax_vv(Register_Status* register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm);
void vminu_vv(Register_Status* register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm);
void vmaxu_vv(Register_Status* register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm);

#endif