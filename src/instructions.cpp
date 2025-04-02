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

void vand_vi(Register_Status * register_status, uint8_t vd,uint8_t vs2,int8_t Imm,uint8_t vm) {        //VAND_VI
    sc_int<64> Imm_extended = Imm;
    printf("\nVand.vi v%d = %d & v%d \n",vd,Imm,vs2);
    if(vm==1){
            for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=reg_status->vtype.SEW) {
                register_status->Vector_Register[vd].range(j+reg_status->vtype.SEW-1 , j) =
                register_status->Vector_Register[vs2].range(j+reg_status->vtype.SEW-1 , j) &  Imm_extended.range(reg_status->vtype.SEW - 1, 0);
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

void vor_vi(Register_Status * register_status, uint8_t vd,uint8_t vs2,int8_t Imm,uint8_t vm) {        //VOR_VI
        sc_int<64> Imm_extended = Imm;
        printf("\nVor.vi v%d = %d | v%d \n",vd,Imm,vs2);
        if(vm==1){
                for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=reg_status->vtype.SEW) {
                    register_status->Vector_Register[vd].range(j+reg_status->vtype.SEW-1 , j) =
                    register_status->Vector_Register[vs2].range(j+reg_status->vtype.SEW-1 , j) |  Imm_extended.range(reg_status->vtype.SEW - 1, 0);
                } 
             }
            else{}
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

void vminu_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {         //VMINU_VV
    printf("\nVminu.vv v%d = min((unsigned)v%d ,(unsigned) v%d)\n",vd,vs1,vs2);
       if (vm == 1) {
            for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=reg_status->vtype.SEW) {
                    register_status->Vector_Register[vd].range(j+reg_status->vtype.SEW-1 , j) =
                    ( register_status->Vector_Register[vs2].range(j+reg_status->vtype.SEW-1 , j).to_uint64() > 
                    register_status->Vector_Register[vs1].range(j+reg_status->vtype.SEW-1 , j).to_uint64() ) ? register_status->Vector_Register[vs1].range(j+reg_status->vtype.SEW-1 , j) :  register_status->Vector_Register[vs2].range(j+reg_status->vtype.SEW-1 , j) ;       
                } 
        } else {}

}

void vmaxu_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {         //VMAXU_VV
    printf("\nVmaxu.vv v%d = max((unsigned)v%d , (unsigned) v%d)\n",vd,vs1,vs2);
       if (vm == 1) {
            for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=reg_status->vtype.SEW) {
                    register_status->Vector_Register[vd].range(j+reg_status->vtype.SEW-1 , j) =
                    ( register_status->Vector_Register[vs2].range(j+reg_status->vtype.SEW-1 , j).to_uint64() > 
                    register_status->Vector_Register[vs1].range(j+reg_status->vtype.SEW-1 , j).to_uint64() ) ? register_status->Vector_Register[vs2].range(j+reg_status->vtype.SEW-1 , j) :  register_status->Vector_Register[vs1].range(j+reg_status->vtype.SEW-1 , j) ;       
                } 
        } else {}

}

void vrgather_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {          //VRGATHER_VV
    printf("\vrgather.vv v%d = v%d[v%d]\n",vd,vs2,vs1);
    uint64 index;
    sc_bv<64> Zero = 0;
       if (vm == 1) {
            for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=reg_status->vtype.SEW) {
                    index = register_status->Vector_Register[vs1].range(j+reg_status->vtype.SEW-1 , j).to_uint64();

                    register_status->Vector_Register[vd].range(j+reg_status->vtype.SEW-1 , j) = ( index >= reg_status->VLMAX) ? 
                    Zero.range(reg_status->vtype.SEW - 1, 0) : register_status->Vector_Register[vs2].range(reg_status->vtype.SEW-1 + index*reg_status->vtype.SEW, index*reg_status->vtype.SEW) ;       
                } 
        } else {}

}

void vrgather_vi(Register_Status *register_status, uint8_t vd, uint8_t vs2, uint8_t Imm, uint8_t vm) {          //VRGATHER_VI
    printf("\vrgather.vi v%d = v%d[%d]\n",vd,vs2,Imm);
    sc_bv<64> Zero = 0;
       if (vm == 1) {
            for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=reg_status->vtype.SEW) {

                    register_status->Vector_Register[vd].range(j+reg_status->vtype.SEW-1 , j) = ( Imm >= reg_status->VLMAX) ? 
                    Zero.range(reg_status->vtype.SEW - 1, 0) : register_status->Vector_Register[vs2].range(reg_status->vtype.SEW-1 + Imm*reg_status->vtype.SEW, Imm*reg_status->vtype.SEW) ;       
                } 
        } else {}

}

void vrgatherei16_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {      //VRGATHEREI16_VV
    printf("\nvrgatherei16.vv v%d = v%d[v%d]\n", vd, vs2, vs1);   
    uint64_t index;                 //each index is 16 bit regardless SEW
    uint64_t bitIndex=0;
    uint64_t ValidIndecies = (VLEN/16)*reg_status->vtype.LMUL-1;
    sc_bv<64> Zero = 0;
       if (vm == 1) {
            for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=reg_status->vtype.SEW) {
                    if(i>ValidIndecies)
                        break;
                    index = register_status->Vector_Register[vs1].range(bitIndex + 15, bitIndex).to_uint64();   //extract each 16 bit as index
                    printf("index %lu = %lu\n",i,index);
                    register_status->Vector_Register[vd].range(j+reg_status->vtype.SEW-1 , j) = ( index >= reg_status->VLMAX) ? 
                    Zero.range(reg_status->vtype.SEW - 1, 0) : register_status->Vector_Register[vs2].range(reg_status->vtype.SEW-1 + index*reg_status->vtype.SEW, index*reg_status->vtype.SEW) ;       

                    bitIndex += 16;         //add 16 bit to navigate to the second index 
                } 
        } else {}

}


void vslideup_vi(Register_Status *register_status, uint8_t vd, uint8_t vs2, uint8_t Imm, uint8_t vm) {          //VSLIDEUP_VI
    uint32_t Vl = reg_status->VL;
    if(Imm>=Vl)
        return;
    printf("\nvslideup_vi v%d[%u] -> v%d[%u] = v%d[0] ->  v%d[%u] \n",vd,Imm,vd,Vl-1,vs2,vs2,Vl-1-Imm);

    if (vm == 1) {
        for (uint64_t i = Imm ; i < Vl; i++) {
                    register_status->Vector_Register[vd].range(i*reg_status->vtype.SEW + reg_status->vtype.SEW-1 , i*reg_status->vtype.SEW) =  
                    register_status->Vector_Register[vs2].range(reg_status->vtype.SEW-1 + (i-Imm)*reg_status->vtype.SEW, (i-Imm)*reg_status->vtype.SEW) ;       
                } 
        } else {}

}

void vslidedown_vi(Register_Status *register_status, uint8_t vd, uint8_t vs2, uint8_t Imm, uint8_t vm) {          //VSLIDEDOWN_VI
    uint32_t Vl = reg_status->VL;
    if(Imm>=Vl)
        return;
    printf("\nvslidedown_vi v%d[0] -> v%d[%u] = v%d[%d] ->  v%d[%u] \n",vd,vd,Vl-Imm-1,vs2,Imm,vs2,Vl-1);

    if (vm == 1) {
        for (uint64_t i = Imm ; i < Vl; i++) {
                    register_status->Vector_Register[vd].range(reg_status->vtype.SEW-1 + (i-Imm)*reg_status->vtype.SEW, (i-Imm)*reg_status->vtype.SEW) =  
                    register_status->Vector_Register[vs2].range(i*reg_status->vtype.SEW + reg_status->vtype.SEW-1 , i*reg_status->vtype.SEW) ;       
                } 
        } else {}

}


