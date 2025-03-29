#include "instructions.h"


///////*                                       INSTRUCTION FUNCTIONS                                      *//////

void vadd_vv(Register_Status * register_status, uint8_t vd, uint8_t vs1, uint8_t vs2,uint8_t vm) {     //VADD_VV
    
    printf("\nVadd.vv v%d = v%d + v%d\n",vd,vs1,vs2);

    if(vm==1){
        for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=reg_status->vtype.SEW) {

            register_status->Vector_Register[vd].range(j+reg_status->vtype.SEW-1 , j) = register_status->Vector_Register[vs1].range(j+reg_status->vtype.SEW-1 , j).to_int64() + 
            register_status->Vector_Register[vs2].range(j+reg_status->vtype.SEW-1 , j).to_int64();
           
        }
    }
    else{}
}

void vadd_vi(Register_Status * register_status, uint8_t vd, uint8_t vs2,int8_t Imm,uint8_t vm) {        //VADD_VI
    sc_int<64> Imm_extended = Imm;
    printf("\nVadd.vi v%d = v%d + %d\n",vd,vs2,Imm);

    if(vm==1){   
        for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=reg_status->vtype.SEW) {
            register_status->Vector_Register[vd].range(j+reg_status->vtype.SEW-1 , j) = Imm_extended.range(reg_status->vtype.SEW - 1, 0).to_int64() + 
            register_status->Vector_Register[vs2].range(j+reg_status->vtype.SEW-1 , j).to_int64();       
        }
    }
    else{}
    }

void vsub_vv(Register_Status * register_status, uint8_t vd, uint8_t vs1, uint8_t vs2,uint8_t vm) {      //VSUB_VV
    printf("\nVsub.vv v%d = v%d - v%d\n",vd,vs2,vs1);
    if(vm==1){
        for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=reg_status->vtype.SEW) {
            register_status->Vector_Register[vd].range(j+reg_status->vtype.SEW-1 , j) =
            register_status->Vector_Register[vs2].range(j+reg_status->vtype.SEW-1 , j).to_int64()-register_status->Vector_Register[vs1].range(j+reg_status->vtype.SEW-1 , j).to_int64();       
        } 
    }
    else{}
}


void vrsub_vi(Register_Status * register_status, uint8_t vd, uint8_t vs2,int8_t Imm,uint8_t vm) {        //Vrsub_VI
    sc_int<64> Imm_extended = Imm;
    printf("\nVrsub.vi v%d = %d - v%d\n",vd,Imm,vs2);
    if(vm==1){   
        for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=reg_status->vtype.SEW) {
            register_status->Vector_Register[vd].range(j+reg_status->vtype.SEW-1 , j) =
            Imm_extended.range(reg_status->vtype.SEW - 1, 0).to_int64() -  register_status->Vector_Register[vs2].range(j+reg_status->vtype.SEW-1 , j).to_int64();
        }
    }
    else{}
}


void vand_vv(Register_Status * register_status, uint8_t vd, uint8_t vs1, uint8_t vs2,uint8_t vm) {      //VAND_VV
    printf("\nVand.vv v%d = v%d & v%d\n",vd,vs1,vs2);
    if(vm==1){
            for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=reg_status->vtype.SEW) {
                register_status->Vector_Register[vd].range(j+reg_status->vtype.SEW-1 , j) =
                register_status->Vector_Register[vs2].range(j+reg_status->vtype.SEW-1 , j) & 
                register_status->Vector_Register[vs1].range(j+reg_status->vtype.SEW-1 , j);       
            } 
        }
    else{}
    }

void vor_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {       //VOR_VV
    printf("\nVor.vv v%d = v%d | v%d\n",vd,vs1,vs2);
    if (vm == 1) {
            for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=reg_status->vtype.SEW) {
                register_status->Vector_Register[vd].range(j+reg_status->vtype.SEW-1 , j) =
                register_status->Vector_Register[vs2].range(j+reg_status->vtype.SEW-1 , j) | 
                register_status->Vector_Register[vs1].range(j+reg_status->vtype.SEW-1 , j);       
              } 
        } else { }
    }

void vxor_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {      //VXOR_VV
    printf("\nVxor.vv v%d = v%d ^ v%d\n",vd,vs1,vs2);
        if (vm == 1) {
            for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=reg_status->vtype.SEW) {
                register_status->Vector_Register[vd].range(j+reg_status->vtype.SEW-1 , j) =
                register_status->Vector_Register[vs2].range(j+reg_status->vtype.SEW-1 , j) ^ 
                register_status->Vector_Register[vs1].range(j+reg_status->vtype.SEW-1 , j);       
              } 
        } else {}
    }


void vxor_vi(Register_Status * register_status, uint8_t vd, uint8_t vs2,int8_t Imm,uint8_t vm) {         //VXOR_VI
    sc_int<64> Imm_extended = Imm;
    printf("\nVxor.vi v%d = %d ^ v%d\n",vd,Imm,vs2);
        if(vm==1){
            for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=reg_status->vtype.SEW) {
                register_status->Vector_Register[vd].range(j+reg_status->vtype.SEW-1 , j) =
                register_status->Vector_Register[vs2].range(j+reg_status->vtype.SEW-1 , j) ^ Imm_extended.range(reg_status->vtype.SEW - 1, 0) ;
                }
            }
        else{}
       }
    
    
void vmv_v_v(Register_Status * register_status , uint8_t vd , uint8_t vs1 , uint8_t vm) {                //VMV.V.V
    printf("\nvmv.v.v v%d = v%d\n",vd,vs1);
        if(vm==1){
            for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=reg_status->vtype.SEW) {
                register_status->Vector_Register[vd].range(j+reg_status->vtype.SEW-1 , j) =
                register_status->Vector_Register[vs1].range(j+reg_status->vtype.SEW-1 , j);
                }
            }
        else{}
}

void vmv_v_i(Register_Status * register_status , uint8_t vd , int8_t Imm , uint8_t vm) {                 //VMV.V.I
    sc_int<64> Imm_extended = Imm;
    printf("\nvmv.v.i v%d = %d\n",vd,Imm);
        if(vm==1){
            for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=reg_status->vtype.SEW) {
                register_status->Vector_Register[vd].range(j + reg_status->vtype.SEW - 1 , j) =  Imm_extended.range(reg_status->vtype.SEW - 1, 0);
                }
            }
        else{}
}

void vmin_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {      //VMIN_VV
    printf("\nVmin.vv v%d = min(v%d , v%d)\n",vd,vs1,vs2);
       if (vm == 1) {
            for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=reg_status->vtype.SEW) {
                    register_status->Vector_Register[vd].range(j+reg_status->vtype.SEW-1 , j) =
                    ( register_status->Vector_Register[vs2].range(j+reg_status->vtype.SEW-1 , j).to_int64() > 
                    register_status->Vector_Register[vs1].range(j+reg_status->vtype.SEW-1 , j).to_int64() ) ? register_status->Vector_Register[vs1].range(j+reg_status->vtype.SEW-1 , j) :  register_status->Vector_Register[vs2].range(j+reg_status->vtype.SEW-1 , j) ;       
                } 
        } else {}

}

void vmax_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {      //VMAX_VV
    printf("\nVmax.vv v%d = max(v%d , v%d)\n",vd,vs1,vs2);
       if (vm == 1) {
            for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=reg_status->vtype.SEW) {
                    register_status->Vector_Register[vd].range(j+reg_status->vtype.SEW-1 , j) =
                    ( register_status->Vector_Register[vs2].range(j+reg_status->vtype.SEW-1 , j).to_int64() > 
                    register_status->Vector_Register[vs1].range(j+reg_status->vtype.SEW-1 , j).to_int64() ) ? register_status->Vector_Register[vs2].range(j+reg_status->vtype.SEW-1 , j) :  register_status->Vector_Register[vs1].range(j+reg_status->vtype.SEW-1 , j) ;       
                } 
        } else {}

}

void vminu_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {      //VMINU_VV
    printf("\nVminu.vv v%d = min((unsigned)v%d ,(unsigned) v%d)\n",vd,vs1,vs2);
       if (vm == 1) {
            for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=reg_status->vtype.SEW) {
                    register_status->Vector_Register[vd].range(j+reg_status->vtype.SEW-1 , j) =
                    ( register_status->Vector_Register[vs2].range(j+reg_status->vtype.SEW-1 , j).to_uint64() > 
                    register_status->Vector_Register[vs1].range(j+reg_status->vtype.SEW-1 , j).to_uint64() ) ? register_status->Vector_Register[vs1].range(j+reg_status->vtype.SEW-1 , j) :  register_status->Vector_Register[vs2].range(j+reg_status->vtype.SEW-1 , j) ;       
                } 
        } else {}

}

void vmaxu_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {      //VMAXU_VV
    printf("\nVmaxu.vv v%d = max((unsigned)v%d , (unsigned) v%d)\n",vd,vs1,vs2);
       if (vm == 1) {
            for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=reg_status->vtype.SEW) {
                    register_status->Vector_Register[vd].range(j+reg_status->vtype.SEW-1 , j) =
                    ( register_status->Vector_Register[vs2].range(j+reg_status->vtype.SEW-1 , j).to_uint64() > 
                    register_status->Vector_Register[vs1].range(j+reg_status->vtype.SEW-1 , j).to_uint64() ) ? register_status->Vector_Register[vs2].range(j+reg_status->vtype.SEW-1 , j) :  register_status->Vector_Register[vs1].range(j+reg_status->vtype.SEW-1 , j) ;       
                } 
        } else {}

}