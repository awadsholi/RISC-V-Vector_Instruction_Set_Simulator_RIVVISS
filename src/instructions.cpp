#include "instructions.h"
#include "functions.h"


/////////*                                       INSTRUCTION FUNCTIONS                                      *////////


void vadd_vv(Register_Status * register_status, uint8_t vd, uint8_t vs1, uint8_t vs2,uint8_t vm) {     //VADD_VV
    printf("\nVadd.vv v%d = v%d + v%d\n",vd,vs1,vs2);
    sc_bv<VLEN> V0 =register_status->Vector_Register[0];

    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)
            register_status->Vector_Register[vd].range(j+register_status->vtype.SEW-1 , j) = register_status->Vector_Register[vs1].range(j+register_status->vtype.SEW-1 , j).to_int64() + 
            register_status->Vector_Register[vs2].range(j+register_status->vtype.SEW-1 , j).to_int64();
        }
    }
}


void vadd_vi(Register_Status * register_status, uint8_t vd, uint8_t vs2,int8_t Imm,uint8_t vm) {        //VADD_VI
    sc_int<64> Imm_extended = Imm;
    printf("\nVadd.vi v%d = v%d + %d\n",vd,vs2,Imm);
    sc_bv<VLEN> V0 =register_status->Vector_Register[0];

    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)
            register_status->Vector_Register[vd].range(j+register_status->vtype.SEW-1 , j) = Imm_extended.range(register_status->vtype.SEW - 1, 0).to_int64() + 
            register_status->Vector_Register[vs2].range(j+register_status->vtype.SEW-1 , j).to_int64();       
        }
    }
}


void vsub_vv(Register_Status * register_status, uint8_t vd, uint8_t vs1, uint8_t vs2,uint8_t vm) {      //VSUB_VV
    printf("\nVsub.vv v%d = v%d - v%d\n",vd,vs2,vs1);
    sc_bv<VLEN> V0 =register_status->Vector_Register[0];

    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)
            register_status->Vector_Register[vd].range(j+register_status->vtype.SEW-1 , j) =
            register_status->Vector_Register[vs2].range(j+register_status->vtype.SEW-1 , j).to_int64()-register_status->Vector_Register[vs1].range(j+register_status->vtype.SEW-1 , j).to_int64();       
        } 
    }
}


void vrsub_vi(Register_Status * register_status, uint8_t vd, uint8_t vs2,int8_t Imm,uint8_t vm) {        //Vrsub_VI
    sc_int<64> Imm_extended = Imm;
    printf("\nVrsub.vi v%d = %d - v%d\n",vd,Imm,vs2);
    sc_bv<VLEN> V0 =register_status->Vector_Register[0];
    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)
            register_status->Vector_Register[vd].range(j+register_status->vtype.SEW-1 , j) =
            Imm_extended.range(register_status->vtype.SEW - 1, 0).to_int64() -  register_status->Vector_Register[vs2].range(j+register_status->vtype.SEW-1 , j).to_int64();
        }
    }
}


void vand_vv(Register_Status * register_status, uint8_t vd, uint8_t vs1, uint8_t vs2,uint8_t vm) {      //VAND_VV
    printf("\nVand.vv v%d = v%d & v%d\n",vd,vs1,vs2);
    sc_bv<VLEN> V0 =register_status->Vector_Register[0];

    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)
            register_status->Vector_Register[vd].range(j+register_status->vtype.SEW-1 , j) =
            register_status->Vector_Register[vs2].range(j+register_status->vtype.SEW-1 , j) & 
            register_status->Vector_Register[vs1].range(j+register_status->vtype.SEW-1 , j);       
        }
    }
}


void vand_vi(Register_Status * register_status, uint8_t vd,uint8_t vs2,int8_t Imm,uint8_t vm) {        //VAND_VI
    sc_int<64> Imm_extended = Imm;
    printf("\nVand.vi v%d = %d & v%d \n",vd,Imm,vs2);
    sc_bv<VLEN> V0 =register_status->Vector_Register[0];

    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)
            register_status->Vector_Register[vd].range(j+register_status->vtype.SEW-1 , j) =
            register_status->Vector_Register[vs2].range(j+register_status->vtype.SEW-1 , j) &  Imm_extended.range(register_status->vtype.SEW - 1, 0);
        } 
    }
}    


void vor_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {       //VOR_VV
    printf("\nVor.vv v%d = v%d | v%d\n",vd,vs1,vs2);
    sc_bv<VLEN> V0 =register_status->Vector_Register[0];
    
    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)
            register_status->Vector_Register[vd].range(j+register_status->vtype.SEW-1 , j) =
            register_status->Vector_Register[vs2].range(j+register_status->vtype.SEW-1 , j) | 
            register_status->Vector_Register[vs1].range(j+register_status->vtype.SEW-1 , j);       
        } 
    }
}


void vor_vi(Register_Status * register_status, uint8_t vd,uint8_t vs2,int8_t Imm,uint8_t vm) {        //VOR_VI
    sc_int<64> Imm_extended = Imm;
    sc_bv<VLEN> V0 =register_status->Vector_Register[0];
    printf("\nVor.vi v%d = %d | v%d \n",vd,Imm,vs2);
    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)
            register_status->Vector_Register[vd].range(j+register_status->vtype.SEW-1 , j) =
            register_status->Vector_Register[vs2].range(j+register_status->vtype.SEW-1 , j) |  Imm_extended.range(register_status->vtype.SEW - 1, 0);
        } 
    }
} 


void vxor_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {      //VXOR_VV
    printf("\nVxor.vv v%d = v%d ^ v%d\n",vd,vs1,vs2);
    sc_bv<VLEN> V0 =register_status->Vector_Register[0];  

    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)
            register_status->Vector_Register[vd].range(j+register_status->vtype.SEW-1 , j) =
            register_status->Vector_Register[vs2].range(j+register_status->vtype.SEW-1 , j) ^ 
            register_status->Vector_Register[vs1].range(j+register_status->vtype.SEW-1 , j);       
        }
    }
}


void vxor_vi(Register_Status * register_status, uint8_t vd, uint8_t vs2,int8_t Imm,uint8_t vm) {         //VXOR_VI
    sc_int<64> Imm_extended = Imm;
    printf("\nVxor.vi v%d = %d ^ v%d\n",vd,Imm,vs2);
    sc_bv<VLEN> V0 =register_status->Vector_Register[0];  

    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)
            register_status->Vector_Register[vd].range(j+register_status->vtype.SEW-1 , j) =
            register_status->Vector_Register[vs2].range(j+register_status->vtype.SEW-1 , j) ^ Imm_extended.range(register_status->vtype.SEW - 1, 0) ;
        }
    } 
}
    
    
void vmv_v_v(Register_Status * register_status , uint8_t vd , uint8_t vs1 , uint8_t vm) {                //VMV.V.V
    printf("\nvmv.v.v v%d = v%d\n",vd,vs1);
    sc_bv<VLEN> V0 =register_status->Vector_Register[0];  

    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)
            register_status->Vector_Register[vd].range(j+register_status->vtype.SEW-1 , j) =
            register_status->Vector_Register[vs1].range(j+register_status->vtype.SEW-1 , j);
        }
    }
}


void vmv_v_i(Register_Status * register_status , uint8_t vd , int8_t Imm , uint8_t vm) {                 //VMV.V.I
    sc_int<64> Imm_extended = Imm;
    printf("\nvmv.v.i v%d = %d\n",vd,Imm);
    sc_bv<VLEN> V0 =register_status->Vector_Register[0];  

    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)
            register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1 , j) =  Imm_extended.range(register_status->vtype.SEW - 1, 0);
        }
    }
}


void vmin_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {      //VMIN_VV
    printf("\nVmin.vv v%d = min(v%d , v%d)\n",vd,vs1,vs2);
    sc_bv<VLEN> V0 =register_status->Vector_Register[0];  

    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)
            register_status->Vector_Register[vd].range(j+register_status->vtype.SEW-1 , j) =
            ( register_status->Vector_Register[vs2].range(j+register_status->vtype.SEW-1 , j).to_int64() > 
            register_status->Vector_Register[vs1].range(j+register_status->vtype.SEW-1 , j).to_int64() ) ? register_status->Vector_Register[vs1].range(j+register_status->vtype.SEW-1 , j) :  register_status->Vector_Register[vs2].range(j+register_status->vtype.SEW-1 , j) ;       
        } 
    }
}


void vmax_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {      //VMAX_VV
    printf("\nVmax.vv v%d = max(v%d , v%d)\n",vd,vs1,vs2);
    sc_bv<VLEN> V0 =register_status->Vector_Register[0];  
    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)
            register_status->Vector_Register[vd].range(j+register_status->vtype.SEW-1 , j) =
            ( register_status->Vector_Register[vs2].range(j+register_status->vtype.SEW-1 , j).to_int64() > 
            register_status->Vector_Register[vs1].range(j+register_status->vtype.SEW-1 , j).to_int64() ) ? register_status->Vector_Register[vs2].range(j+register_status->vtype.SEW-1 , j) :  register_status->Vector_Register[vs1].range(j+register_status->vtype.SEW-1 , j) ;       
        }
    }
}


void vminu_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {         //VMINU_VV
    printf("\nVminu.vv v%d = min((unsigned)v%d ,(unsigned) v%d)\n",vd,vs1,vs2);
    sc_bv<VLEN> V0 =register_status->Vector_Register[0];  

    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)
            register_status->Vector_Register[vd].range(j+register_status->vtype.SEW-1 , j) =
            ( register_status->Vector_Register[vs2].range(j+register_status->vtype.SEW-1 , j).to_uint64() > 
            register_status->Vector_Register[vs1].range(j+register_status->vtype.SEW-1 , j).to_uint64() ) ? register_status->Vector_Register[vs1].range(j+register_status->vtype.SEW-1 , j) :  register_status->Vector_Register[vs2].range(j+register_status->vtype.SEW-1 , j) ;       
        } 
    }
}


void vmaxu_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {         //VMAXU_VV
    printf("\nVmaxu.vv v%d = max((unsigned)v%d , (unsigned) v%d)\n",vd,vs1,vs2);
    sc_bv<VLEN> V0 =register_status->Vector_Register[0];  

    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)
            register_status->Vector_Register[vd].range(j+register_status->vtype.SEW-1 , j) =
            ( register_status->Vector_Register[vs2].range(j+register_status->vtype.SEW-1 , j).to_uint64() > 
            register_status->Vector_Register[vs1].range(j+register_status->vtype.SEW-1 , j).to_uint64() ) ? register_status->Vector_Register[vs2].range(j+register_status->vtype.SEW-1 , j) :  register_status->Vector_Register[vs1].range(j+register_status->vtype.SEW-1 , j) ;       
        } 
    }
}


void vrgather_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {          //VRGATHER_VV
    printf("\vrgather.vv v%d = v%d[v%d]\n",vd,vs2,vs1);
    uint64 index;
    sc_bv<64> Zero = 0; 
    sc_bv<VLEN> V0 =register_status->Vector_Register[0];  

    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)
            index = register_status->Vector_Register[vs1].range(j+register_status->vtype.SEW-1 , j).to_uint64();
            register_status->Vector_Register[vd].range(j+register_status->vtype.SEW-1 , j) = ( index >= register_status->VLMAX) ? 
            Zero.range(register_status->vtype.SEW - 1, 0) : register_status->Vector_Register[vs2].range(register_status->vtype.SEW-1 + index*register_status->vtype.SEW, index*register_status->vtype.SEW) ;       
        } 
    }
}


void vrgather_vi(Register_Status *register_status, uint8_t vd, uint8_t vs2, uint8_t Imm, uint8_t vm) {          //VRGATHER_VI
    printf("\vrgather.vi v%d = v%d[%d]\n",vd,vs2,Imm);
    sc_bv<64> Zero = 0;
    sc_bv<VLEN> V0 =register_status->Vector_Register[0]; 

    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)
            register_status->Vector_Register[vd].range(j+register_status->vtype.SEW-1 , j) = ( Imm >= register_status->VLMAX) ? 
            Zero.range(register_status->vtype.SEW - 1, 0) : register_status->Vector_Register[vs2].range(register_status->vtype.SEW-1 + Imm*register_status->vtype.SEW, Imm*register_status->vtype.SEW) ;       
        } 
    }
}


void vrgatherei16_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {      //VRGATHEREI16_VV
    printf("\nvrgatherei16.vv v%d = v%d[v%d]\n", vd, vs2, vs1);   
    uint16_t index;                                          //each index is 16 bit regardless SEW
    sc_bv<VLEN> V0 =register_status->Vector_Register[0];  
    sc_bv<64> Zero = 0;

    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)
            index = register_status->Vector_Register[vs1].range(j+register_status->vtype.SEW-1 , j).to_uint64();     //extract each 16 bit as index
            register_status->Vector_Register[vd].range(j+register_status->vtype.SEW-1 , j) = ( index >= register_status->VLMAX) ? 
            Zero.range(register_status->vtype.SEW - 1, 0) : register_status->Vector_Register[vs2].range(register_status->vtype.SEW-1 + index*register_status->vtype.SEW, index*register_status->vtype.SEW) ;       
        }
    }
}


void vslideup_vi(Register_Status *register_status, uint8_t vd, uint8_t vs2, uint8_t Imm, uint8_t vm) {          //VSLIDEUP_VI
    uint32_t Vl = register_status->VL;
    sc_bv<VLEN> V0 =register_status->Vector_Register[0];  
    if(Imm>=Vl)
        return;
    printf("\nvslideup_vi v%d[%u] -> v%d[%u] = v%d[0] ->  v%d[%u] \n",vd,Imm,vd,Vl-1,vs2,vs2,Vl-1-Imm);

    for (uint64_t i = Imm ; i < Vl; i++) {
        if(vm==1 || V0.range(i*register_status->vtype.SEW + register_status->vtype.SEW-1 , i*register_status->vtype.SEW).to_uint()==1){

            register_status->Vector_Register[vd].range(i*register_status->vtype.SEW + register_status->vtype.SEW-1 , i*register_status->vtype.SEW) =  
            register_status->Vector_Register[vs2].range(register_status->vtype.SEW-1 + (i-Imm)*register_status->vtype.SEW, (i-Imm)*register_status->vtype.SEW) ;       
        } 
    }
}


void vslidedown_vi(Register_Status *register_status, uint8_t vd, uint8_t vs2, uint8_t Imm, uint8_t vm) {          //VSLIDEDOWN_VI
    uint32_t Vl = register_status->VL;
    sc_bv<VLEN> V0 =register_status->Vector_Register[0];  
    if(Imm>=Vl)
        return;
    printf("\nvslidedown_vi v%d[0] -> v%d[%u] = v%d[%d] ->  v%d[%u] \n",vd,vd,Vl-Imm-1,vs2,Imm,vs2,Vl-1);

    for (uint64_t i = Imm ; i < Vl; i++) {
        if (vm == 1 || V0.range(register_status->vtype.SEW-1 + (i-Imm)*register_status->vtype.SEW, (i-Imm)*register_status->vtype.SEW).to_uint()==1){               //Checking Masking (Active elements)

            register_status->Vector_Register[vd].range(register_status->vtype.SEW-1 + (i-Imm)*register_status->vtype.SEW, (i-Imm)*register_status->vtype.SEW) =  
            register_status->Vector_Register[vs2].range(i*register_status->vtype.SEW + register_status->vtype.SEW-1 , i*register_status->vtype.SEW) ;       
        } 
    }
}


void vsaddu_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {         //VSADDU_VV
    printf("\nVsaddu.vv v%d = clamp((unsigned)v%d + (unsigned) v%d)\n",vd,vs2,vs1);
    uint64_t sum;
    uint64_t max_value;
    sc_bv<VLEN> V0 =register_status->Vector_Register[0];  

    if (register_status->vtype.SEW == 64) 
        max_value = UINT64_MAX;
    else 
        max_value = (1ULL << register_status->vtype.SEW) - 1ULL;
    
    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)

            uint64_t vs2_val = register_status->Vector_Register[vs2].range(j + register_status->vtype.SEW - 1, j).to_uint64();
            uint64_t vs1_val = register_status->Vector_Register[vs1].range(j + register_status->vtype.SEW - 1, j).to_uint64();
            bool overflow = false;
            if ((vs2_val > max_value - vs1_val)){
                overflow = true;    
                register_status->vcsr[0]=1;            //Set the saturation flag (vxsat)
            }
            sum = vs2_val + vs1_val;
            if (overflow)
                register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j) = max_value;    
            else 
                register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j) = sum;
        } 
    }
}


void vsaddu_vi(Register_Status *register_status, uint8_t vd, uint8_t vs2, uint8_t Imm, uint8_t vm) {         //VSADDU_VI

    printf("\nVsaddu.vi v%d = clamp((unsigned)v%d + %d)\n",vd,vs2,Imm);
    uint64_t sum;
    uint64_t max_value;
    sc_bv<VLEN> V0 =register_status->Vector_Register[0];  

    if (register_status->vtype.SEW == 64) 
        max_value = UINT64_MAX;
    else 
        max_value = (1ULL << register_status->vtype.SEW) - 1ULL;
    
    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)

            uint64_t vs2_val = register_status->Vector_Register[vs2].range(j + register_status->vtype.SEW - 1, j).to_uint64();
            bool overflow = false;
            if ((vs2_val > max_value - Imm)){
                register_status->vcsr[0]=1;            //Set the saturation flag (vxsat)
                overflow = true;    
            }
            sum = vs2_val + Imm;
            if (overflow)
                register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j) = max_value;    
            else 
                register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j) = sum;
        } 
    } 
}



void vsadd_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {             //VSADD_VV
    printf("\nVsadd_vv v%d = clamp (v%d + v%d)\n", vd, vs2, vs1);    
    int64_t sum;
    int64_t max_val, min_val;
    sc_bv<VLEN> V0 =register_status->Vector_Register[0];  

    if (register_status->vtype.SEW == 64) {
        max_val = INT64_MAX;   
        min_val = INT64_MIN; 
    } else {
        max_val = (1LL << (register_status->vtype.SEW - 1)) - 1;   // Signed range based on SEW value
        min_val = -(1LL << (register_status->vtype.SEW - 1));      
    }
    
    for (uint64_t i = 0, j = 0; i < register_status->VL; i++, j += register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)

            int64_t vs2_val = register_status->Vector_Register[vs2].range(j + register_status->vtype.SEW - 1, j).to_int64();
            int64_t vs1_val = register_status->Vector_Register[vs1].range(j + register_status->vtype.SEW - 1, j).to_int64();
            bool overflow = false;
            if ((vs1_val > 0 && vs2_val > max_val - vs1_val) || (vs1_val < 0 && vs2_val < min_val - vs1_val)) {
                register_status->vcsr[0]=1;            //Set the saturation flag (vxsat)
                overflow = true;    
            }           
            sum = vs2_val + vs1_val;           
            if (overflow){
                if(register_status->vtype.SEW == 64)
                    register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j) = (sum > 0) ? min_val : max_val;
                else    
                    register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j) = (sum > 0) ? max_val : min_val;
            }
            else 
                register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j) = sum;   
        }
    } 
}


void vsadd_vi(Register_Status *register_status, uint8_t vd, uint8_t vs2, int8_t Imm, uint8_t vm) {             //VSADD_VI
    printf("\nVsadd_vi v%d = clamp (v%d + %d)\n", vd, vs2, Imm); 
    int64_t sum;
    int64_t max_val, min_val;
    sc_bv<VLEN> V0 =register_status->Vector_Register[0]; 

    if (register_status->vtype.SEW == 64) {
        max_val = INT64_MAX;   
        min_val = INT64_MIN; 
    } else {
        max_val = (1LL << (register_status->vtype.SEW - 1)) - 1;   // Signed range based on SEW value
        min_val = -(1LL << (register_status->vtype.SEW - 1));      
    }
    
    for (uint64_t i = 0, j = 0; i < register_status->VL; i++, j += register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)
            int64_t vs2_val = register_status->Vector_Register[vs2].range(j + register_status->vtype.SEW - 1, j).to_int64();        
            bool overflow = false;
            if ((Imm > 0 && vs2_val > max_val - Imm) || (Imm < 0 && vs2_val < min_val - Imm)) {
                register_status->vcsr[0]=1;            //Set the saturation flag (vxsat)
                overflow = true;    
            }
            sum = vs2_val + Imm;    
            if (overflow){
                if(register_status->vtype.SEW == 64)
                    register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j) = (sum > 0) ? min_val : max_val;
                else    
                    register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j) = (sum > 0) ? max_val : min_val;
                }
            else 
                register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j) = sum;
            
        }
    }
}


void vssubu_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {         //VSSUBU_VV
    printf("\nVssubu.vv v%d = clamp((unsigned)v%d - (unsigned) v%d)\n",vd,vs2,vs1);
    sc_bv<64> Zero = 0;
    sc_bv<VLEN> V0 =register_status->Vector_Register[0]; 
    
    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)
            uint64_t vs2_val = register_status->Vector_Register[vs2].range(j + register_status->vtype.SEW - 1, j).to_uint64();
            uint64_t vs1_val = register_status->Vector_Register[vs1].range(j + register_status->vtype.SEW - 1, j).to_uint64();
            if (vs2_val < vs1_val){          //underflow 
                register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j) = Zero.range(register_status->vtype.SEW - 1,0);    
                register_status->vcsr[0]=1;            //Set the saturation flag (vxsat)
            }     
            else 
                register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j) = vs2_val-vs1_val;    
        }
    }
}


void vssub_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {             //VSSUB_VV
    printf("\nVssub.vv v%d = clamp (v%d - v%d)\n", vd, vs2, vs1);
    int64_t sub;
    int64_t max_val, min_val;
    sc_bv<VLEN> V0 =register_status->Vector_Register[0]; 

    if (register_status->vtype.SEW == 64) {
        max_val = INT64_MAX;   
        min_val = INT64_MIN; 
    } else {
        max_val = (1LL << (register_status->vtype.SEW - 1)) - 1;   // Signed range based on SEW value
        min_val = -(1LL << (register_status->vtype.SEW - 1));      
    }
    
    for (uint64_t i = 0, j = 0; i < register_status->VL; i++, j += register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)

            int64_t vs2_val = register_status->Vector_Register[vs2].range(j + register_status->vtype.SEW - 1, j).to_int64();
            int64_t vs1_val = register_status->Vector_Register[vs1].range(j + register_status->vtype.SEW - 1, j).to_int64();
            bool overflow = false;
            if ((vs2_val > 0 && vs1_val < 0 && vs2_val > max_val + vs1_val) || (vs2_val < 0 && vs1_val > 0 && vs2_val < min_val + vs1_val)){    
                overflow = true;
                register_status->vcsr[0]=1;            //Set the saturation flag (vxsat)
            }
            sub = vs2_val - vs1_val;
            
            if (overflow){
                if(register_status->vtype.SEW == 64)
                    register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j) = (sub > 0) ? min_val : max_val;
                else    
                    register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j) = (sub > 0) ? max_val : min_val;
            }
            else 
                register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j) = sub;
        }
    }
}


void vsll_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {         //VSLL_VV
    uint8_t Shift_amount ;
    printf("\nVsll.vv v%d = (v%d << v%d)\n",vd,vs2,vs1);
    sc_bv<VLEN> V0 =register_status->Vector_Register[0]; 

    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)

            uint64_t vs1_val = register_status->Vector_Register[vs1].range(j + register_status->vtype.SEW - 1, j).to_uint64();   
            Shift_amount =  vs1_val % register_status->vtype.SEW;               //Shift by the lowest (SEW-1) bits 
            register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j) = register_status->Vector_Register[vs2].range(j + register_status->vtype.SEW - 1, j).to_uint64() << Shift_amount;                
        } 
    }   
}


void vsll_vi(Register_Status *register_status, uint8_t vd, uint8_t vs2, uint8_t Imm, uint8_t vm) {         //VSLL_VI
    uint8_t Shift_amount = Imm % register_status->vtype.SEW;             //Shift by the lowest (SEW-1) bits
    printf("\nVsll.vi v%d = (v%d << %d)\n",vd,vs2,Shift_amount);
    sc_bv<VLEN> V0 =register_status->Vector_Register[0]; 

    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {   
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)
            register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j) = register_status->Vector_Register[vs2].range(j + register_status->vtype.SEW - 1, j).to_uint64() << Shift_amount;
        } 
    }
}


void vsrl_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {         //VSRL_VV
    uint8_t Shift_amount;
    printf("\nVsrl.vv v%d = (v%d >> v%d)\n",vd,vs2,vs1);
    sc_bv<VLEN> V0 =register_status->Vector_Register[0]; 

    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)
           
            uint64_t vs1_val = register_status->Vector_Register[vs1].range(j + register_status->vtype.SEW - 1, j).to_uint64();
            Shift_amount =  vs1_val % register_status->vtype.SEW;               //Shift by the lowest (SEW-1) bits 
            register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j) = register_status->Vector_Register[vs2].range(j + register_status->vtype.SEW - 1, j).to_uint64() >> Shift_amount;                
        } 
    }
}


void vsrl_vi(Register_Status *register_status, uint8_t vd, uint8_t vs2, uint8_t Imm, uint8_t vm) {         //VSRL_VI
    
    uint8_t Shift_amount = Imm % register_status->vtype.SEW;             //Shift by the lowest (SEW-1) bits
    printf("\nVsrl.vi v%d = (v%d >> %d)\n",vd,vs2,Shift_amount);
    sc_bv<VLEN> V0 =register_status->Vector_Register[0]; 

    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {   
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)                                                          
        
            register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j) = register_status->Vector_Register[vs2].range(j + register_status->vtype.SEW - 1, j).to_uint64() >> Shift_amount;
        } 
    }
}


void vsra_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {         //VSRA_VV
    uint64_t shift_amt ;
    sc_bv<VLEN> V0 =register_status->Vector_Register[0]; 
    printf("\nVsra.vv v%d = Airthmetic (v%d >> v%d)\n",vd,vs2,vs1);
    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)                                                 
            
            uint64_t vs1_val = register_status->Vector_Register[vs1].range(j + register_status->vtype.SEW - 1, j).to_uint64();
            shift_amt = vs1_val %register_status->vtype.SEW ;                               //Shift by the lowest (SEW-1) bits
            register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j) = register_status->Vector_Register[vs2].range(j + register_status->vtype.SEW - 1, j).to_int64() >> shift_amt;                
        } 
    }
}


void vsra_vi(Register_Status *register_status, uint8_t vd, uint8_t vs2, uint8_t Imm, uint8_t vm) {         //VSRA_VI
    uint8_t shift_amt = Imm % register_status->vtype.SEW ;
    sc_bv<VLEN> V0 =register_status->Vector_Register[0]; 
    printf("\nVsra.vi v%d = (v%d >> %d)\n",vd,vs2,shift_amt);

    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)                                                 
            register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j) = register_status->Vector_Register[vs2].range(j + register_status->vtype.SEW - 1, j).to_int64() >> shift_amt;                
        }   
    }
}


void vsmul_vv(Register_Status *register_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {             //VSMUL_VV
    printf("\nVsmul.vv v%d[i] = clip(roundoff_signed(v%d[i] * v%d[i] , %d )\n", vd, vs2, vs1,register_status->vtype.SEW-1);
    sc_bigint<128>  Mul;
    uint8_t Rounding_Mode = register_status->vcsr.range(2,1).to_uint();
    sc_bv<VLEN> V0 =register_status->Vector_Register[0]; 
    int64_t max_val, min_val;

    if (register_status->vtype.SEW == 64) {
        max_val = INT64_MAX;   
        min_val = INT64_MIN; 
    } else {
        max_val = (1LL << (register_status->vtype.SEW - 1)) - 1;                                // Signed range based on SEW value
        min_val = -(1LL << (register_status->vtype.SEW - 1));      
    }
    for (uint64_t i = 0, j = 0; i < register_status->VL; i++, j += register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)                                                 

            int64_t vs2_val = register_status->Vector_Register[vs2].range(j + register_status->vtype.SEW - 1, j).to_int64();
            int64_t vs1_val = register_status->Vector_Register[vs1].range(j + register_status->vtype.SEW - 1, j).to_int64();

            Mul = sc_bigint<128>(vs2_val) * sc_bigint<128>(vs1_val);              //assign Mul as big int to store the largest possible result

            Mul = sc_bigint<128>(RoundOff(Mul,register_status->vtype.SEW - 1,Rounding_Mode,1));  //Apply round off 

            if(Mul>max_val){                                                      //saturation conditions
                register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j) =  max_val ;
                register_status->vcsr[0]=1;                                       //Set the saturation flag (vxsat)
            }
            else if(Mul<min_val){
                register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j) =  min_val ;
                register_status->vcsr[0]=1;                                       //Set the saturation flag (vxsat)
            }
            else
                register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j) =  Mul.range(register_status->vtype.SEW - 1,0) ;       //casting to number of bit (SEW)
        }
    }
}


void vssrl_vv(Register_Status *register_status, uint8_t vd, uint8_t vs2, uint8_t vs1, uint8_t vm) {         //VSSRL_VV
    uint64_t shift_amt ;
    sc_bv<128> temp=0;            //to convert the value to 128 bit
    uint8_t Rounding_Mode = register_status->vcsr.range(2,1).to_uint();
    sc_bv<VLEN> V0 =register_status->Vector_Register[0]; 
    printf("\nVssrl.vv v%d = round_off(v%d , v%d)\n",vd,vs2,vs1);

    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)                                                 
            uint64_t vs1_val = register_status->Vector_Register[vs1].range(j + register_status->vtype.SEW - 1, j).to_uint64();
            shift_amt = vs1_val % register_status->vtype.SEW;
            temp.range(register_status->vtype.SEW-1,0)=register_status->Vector_Register[vs2].range(j + register_status->vtype.SEW - 1, j);
            register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j)
            = RoundOff(temp,shift_amt,Rounding_Mode,0).range(register_status->vtype.SEW-1,0);  //Apply round off function (unsigned) 
        }
    }
}


void vssrl_vi(Register_Status *register_status, uint8_t vd, uint8_t vs2, uint8_t Imm, uint8_t vm) {         //VSSRL_VI
    
    uint64_t shift_amt = Imm % register_status->vtype.SEW ;
    sc_bv<128> temp=0;            //to convert the value to 128 bit
    uint8_t Rounding_Mode = register_status->vcsr.range(2,1).to_uint();
    sc_bv<VLEN> V0 =register_status->Vector_Register[0]; 
    printf("\nVssrl.vi v%d = round_off(v%d , %d)\n",vd,vs2,shift_amt);

    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)                                                           
            temp.range(register_status->vtype.SEW-1,0)=register_status->Vector_Register[vs2].range(j + register_status->vtype.SEW - 1, j);
            register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j)
            = RoundOff(temp,shift_amt,Rounding_Mode,0).range(register_status->vtype.SEW-1,0);  //Apply round off function (unsigned) 
        }
    }
}


void vssra_vv(Register_Status *register_status, uint8_t vd, uint8_t vs2, uint8_t vs1, uint8_t vm) {         //VSSRA_VV
    uint64_t shift_amt ;
    sc_bigint<128> temp;            //to convert the value to 128 bit
    uint8_t Rounding_Mode = register_status->vcsr.range(2,1).to_uint();
    sc_bv<VLEN> V0 =register_status->Vector_Register[0]; 
    printf("\nVssra.vv v%d = round_off(v%d , v%d)\n",vd,vs2,vs1);

    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)                                                 
            uint64_t vs1_val = register_status->Vector_Register[vs1].range(j + register_status->vtype.SEW - 1, j).to_uint64();
            shift_amt = vs1_val % register_status->vtype.SEW;
            temp=register_status->Vector_Register[vs2].range(j + register_status->vtype.SEW - 1, j).to_int64();
            register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j)
            = RoundOff(temp,shift_amt,Rounding_Mode,1).range(register_status->vtype.SEW-1,0);  //Apply round off function (signed) 
        }
    }
}


void vssra_vi(Register_Status *register_status, uint8_t vd, uint8_t vs2, uint8_t Imm, uint8_t vm) {         //VSSRA_VI
    uint64_t shift_amt = Imm % register_status->vtype.SEW;;
    sc_bigint<128> temp;            //to convert the value to 128 bit
    uint8_t Rounding_Mode = register_status->vcsr.range(2,1).to_uint();
    sc_bv<VLEN> V0 =register_status->Vector_Register[0]; 
    printf("\nVssra.vi v%d = round_off(v%d , %d)\n",vd,vs2,shift_amt);

    for (uint64_t i = 0,j = 0; i < register_status->VL; i++, j+=register_status->vtype.SEW) {
        if (vm == 1 || V0.range(j+register_status->vtype.SEW-1 , j).to_uint()==1){               //Checking Masking (Active elements)                                                 
            temp=register_status->Vector_Register[vs2].range(j + register_status->vtype.SEW - 1, j).to_int64();
            register_status->Vector_Register[vd].range(j + register_status->vtype.SEW - 1, j)
            = RoundOff(temp,shift_amt,Rounding_Mode,1).range(register_status->vtype.SEW-1,0);  //Apply round off function (signed) 
        }
    }
}

            /*          MASKING INSTRUCTIONS            */

void vadc_vvm(Register_Status* reg_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {  
    // vadc.vvm : mask register v0 is used for carry-in
    printf("\033[34m\nVadc.vvm v%d = v%d + v%d + v0[i]\n\033[0m", vd, vs2, vs1);

    int SEW = reg_status->vtype.SEW; // Defining the SEW configured
    uint32_t VL = reg_status->VL; // Defining the VL

    for (uint32_t i = 0; i < VL; i++) {
        // Calculate bit offset for current element
        uint32_t bit_offset = i * SEW;
        // Extract vs1 and vs2 elements
        uint64_t vs1_val = reg_status->Vector_Register[vs1].range(bit_offset + SEW - 1, bit_offset).to_uint64();
        uint64_t vs2_val = reg_status->Vector_Register[vs2].range(bit_offset + SEW - 1, bit_offset).to_uint64();
        // Get carry-in from v0[i] (mask register)
        bool carry_in = (reg_status->Vector_Register[0].range(bit_offset + SEW - 1, bit_offset).to_uint() != 0);
        // Calculate max value based on SEW
        uint64_t max_value = (SEW == 64) ? UINT64_MAX : (1ULL << SEW) - 1ULL;       

// Check if overflow occurs
if ((vs2_val > max_value - vs1_val - carry_in)) {
    // Handle overflow: wrap the result within the range
    uint64_t sum = (vs2_val + vs1_val + carry_in) % max_value-1;  // Wrap around
    reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) = sum;
} else {
    // No overflow: directly store the sum
    reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) = vs2_val + vs1_val + carry_in;
}
    }
    printf("\n\n_______________________\n\n");
}


void vadc_vim(Register_Status* reg_status, uint8_t vd, uint8_t Imm, uint8_t vs2, uint8_t vm) {  
    // vadc.vim : mask register v0 is used for carry-in
    printf("\033[34m\nVadc.vim v%d = v%d + imm(%d) + v0[i]\n\033[0m", vd, vs2, Imm);

    int SEW = reg_status->vtype.SEW; // Defining the SEW configured
    uint32_t VL = reg_status->VL; // Defining the VL
    
    for (uint32_t i = 0; i < VL; i++) {
        // Calculate bit offset for current element
        uint32_t bit_offset = i * SEW;

        // Extract vs1 and vs2 elements
        //int64_t signed_imm = static_cast<int64_t>(Imm);
        int8_t imm5 = static_cast<int8_t>(Imm << 3) >> 3;  // Extract 5-bit signed value
        int64_t signed_imm = static_cast<int64_t>(imm5);     // Sign-extend to 64 bits
        uint64_t vs2_val = reg_status->Vector_Register[vs2].range(bit_offset + SEW - 1, bit_offset).to_uint64();
        // Get carry-in from v0[i] (mask register)
        bool carry_in = (reg_status->Vector_Register[0].range(bit_offset + SEW - 1, bit_offset).to_uint() != 0);
        // Calculate max value based on SEW
        uint64_t max_value = (SEW == 64) ? UINT64_MAX : (1ULL << SEW) - 1ULL;

// Check if overflow occurs
if ((vs2_val > max_value - signed_imm - carry_in)) {
    // Handle overflow: wrap the result within the range
    uint64_t sum = (vs2_val + signed_imm + carry_in) % max_value;  // Wrap around
    reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) = sum;
} else {
    // No overflow: directly store the sum
    reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) = vs2_val + signed_imm + carry_in;
}
    }
    printf("\n\n_______________________\n\n");
}


void vmadc_vvm(Register_Status* reg_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {  
    // vmadc.vvm : mask register v0 is used for carry-in
    if (vm == 0){
        printf("\033[34m\nVmadc.vvm v%d = v%d + v%d + v0[i]\n\033[0m", vd, vs2, vs1);
    }
    else{
        printf("\033[34m\nVmadc.vv v%d = v%d + v%d\n\033[0m", vd, vs2, vs1);
    }

    int SEW = reg_status->vtype.SEW; // Defining the SEW configured
    uint32_t VL = reg_status->VL; // Defining the VL

    for (uint32_t i = 0; i < VL; i++) {
        // Calculate bit offset for current element
        uint32_t bit_offset = i * SEW;
        // Extract vs1 and vs2 elements
        uint64_t vs1_val = reg_status->Vector_Register[vs1].range(bit_offset + SEW - 1, bit_offset).to_uint64();
        uint64_t vs2_val = reg_status->Vector_Register[vs2].range(bit_offset + SEW - 1, bit_offset).to_uint64();
        // Get carry-in from v0[i] (mask register)
        bool carry_in = (reg_status->Vector_Register[0].range(bit_offset + SEW - 1, bit_offset).to_uint() != 0);       
        // Compute sum with carry
        uint64_t max_value = (SEW == 64) ? UINT64_MAX : (1ULL << SEW) - 1ULL;  // max value based on SEW
       
        // Check if overflow occurs
if (((int64_t)(vs2_val) > (int64_t)(max_value - vs1_val - carry_in) )) {
    // Handle overflow: wrap the result within the range
    reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) = 1;
} else {
    // No overflow: directly store the sum
    reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) = 0;
}
    }
    printf("\n\n_______________________\n\n");
}


void vmadc_vi(Register_Status* reg_status, uint8_t vd, uint8_t Imm, uint8_t vs2, uint8_t vm) {  
    // vmadc.vi/m : mask register v0 is used for carry-in
    if (vm == 0){
        printf("\033[34m\nVmadc.vim v%d.mask[i] = Carry_Out(v%d + imm(%d) + v0[i])\n\033[0m", vd, vs2, Imm);
    }
    else{
        printf("\033[34m\nVmadc.vi v%d.mask[i] = Carry_Out( v%d + imm(%d) )\n\033[0m", vd, vs2, Imm);
    }

    int SEW = reg_status->vtype.SEW; // Defining the SEW configured
    uint32_t VL = reg_status->VL; // Defining the VL
    
    for (uint32_t i = 0; i < VL; i++) {
        // Calculate bit offset for current element
        uint32_t bit_offset = i * SEW;

        // Extract vs1 and vs2 elements
        int8_t imm5 = static_cast<int8_t>(Imm << 3) >> 3;  // Extract 5-bit signed value
        int64_t signed_imm = static_cast<int64_t>(imm5);     // Sign-extend to 64 bits
        uint64_t imm_unsigned = static_cast<uint64_t>(signed_imm) & ((1ULL << SEW) - 1);
        uint64_t vs2_val = reg_status->Vector_Register[vs2].range(bit_offset + SEW - 1, bit_offset).to_uint64();
        // Get carry-in from v0[i] (mask register)
        bool carry_in = 0;
        if (vm == 0){
            carry_in = (reg_status->Vector_Register[0].range(bit_offset + SEW - 1, bit_offset).to_uint() != 0);
        }
        // Calculate max value based on SEW
        uint64_t max_value = (SEW == 64) ? UINT64_MAX : (1ULL << SEW) - 1ULL;

// Check if overflow occurs
if (((int64_t)(vs2_val) > (int64_t)(max_value - imm_unsigned - carry_in))) {
    reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) = 1;  // Set carry-out to 1
} else {
    // No overflow: zero as carry-out
    reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) = 0; 
}
    }
    printf("\n\n_______________________\n\n");
}


void vsbc_vvm(Register_Status* reg_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {
    printf("\033[34m\nvsbc.vvm v%d = v%d - v%d - v0[i]\n\033[0m", vd, vs2, vs1);

    int SEW = reg_status->vtype.SEW;
    uint32_t VL = reg_status->VL;

    for (uint32_t i = 0; i < VL; i++) {
        uint32_t bit_offset = i * SEW;

        uint64_t vs2_val = reg_status->Vector_Register[vs2].range(bit_offset + SEW - 1, bit_offset).to_uint64();
        uint64_t vs1_val = reg_status->Vector_Register[vs1].range(bit_offset + SEW - 1, bit_offset).to_uint64();
        bool borrow_in = reg_status->Vector_Register[0].range(bit_offset + SEW - 1, bit_offset).to_uint64() != 0;

        __int128_t raw_result = (__int128_t)vs2_val - (__int128_t)vs1_val - (__int128_t)borrow_in;
        uint64_t result = (uint64_t)raw_result;  // Wrap around "2's complement"
        bool borrow_out = (raw_result < 0);
        reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) = result;
    }
    printf("\n\n_______________________\n\n");
}


void vmsbc_vv(Register_Status* reg_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {
    if(vm == 0){
        printf("\033[34m\nvmsbc.vvm v%d = v%d - v%d - v0[i]\n\033[0m", vd, vs2, vs1);
    }else{
        printf("\033[34m\nvmsbc.vv v%d = v%d - v%d \n\033[0m", vd, vs2, vs1);
    }

    int SEW = reg_status->vtype.SEW;
    uint32_t VL = reg_status->VL;

    for (uint32_t i = 0; i < VL; i++) {
        uint32_t bit_offset = i * SEW;

        uint64_t vs2_val = reg_status->Vector_Register[vs2].range(bit_offset + SEW - 1, bit_offset).to_uint64();
        uint64_t vs1_val = reg_status->Vector_Register[vs1].range(bit_offset + SEW - 1, bit_offset).to_uint64();

        bool borrow_in = 0;
        if (vm == 0){
            borrow_in = reg_status->Vector_Register[0].range(bit_offset + SEW - 1, bit_offset).to_uint64() != 0;
        }

        __int128_t raw_result = (__int128_t)vs2_val - (__int128_t)vs1_val - (__int128_t)borrow_in;
        uint64_t result = (uint64_t)raw_result;  // Wrap around "2's complement"
        bool borrow_out = (raw_result < 0);
        reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) = borrow_out;

    }

    printf("\n\n_______________________\n\n");
}


void vmerge_vvm(Register_Status* reg_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {
    printf("\033[34m\nvmerge.vvm  v%d[i] = v0.mask[i] ? v%d[i] : v%d[i]\n\033[0m", vd, vs1, vs2);


    int SEW = reg_status->vtype.SEW;
    uint32_t VL = reg_status->VL;

    for (uint32_t i = 0; i < VL; i++) {
        uint32_t bit_offset = i * SEW;
        uint64_t vs2_val = reg_status->Vector_Register[vs2].range(bit_offset + SEW - 1, bit_offset).to_uint64();
        uint64_t vs1_val = reg_status->Vector_Register[vs1].range(bit_offset + SEW - 1, bit_offset).to_uint64();
        bool mask = reg_status->Vector_Register[0].range(bit_offset + SEW - 1, bit_offset).to_uint64() != 0;
        reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  (mask != 0) ? vs1_val: vs2_val;
    }

    printf("\n\n_______________________\n\n");
}


void vmerge_vim(Register_Status* reg_status, uint8_t vd, uint8_t Imm, uint8_t vs2, uint8_t vm) {
    printf("\033[34m\nvmerge.vim  v%d[i] = v0.mask[i] ? Imm(%d) : v%d[i]\n\033[0m", vd, Imm, vs2);

    int SEW = reg_status->vtype.SEW;
    uint32_t VL = reg_status->VL;
    int8_t imm5 = static_cast<int8_t>(Imm << 3) >> 3;  // Extract 5-bit signed value
    int64_t signed_imm = static_cast<int64_t>(imm5);     // Sign-extend to 64 bits

    for (uint32_t i = 0; i < VL; i++) {
        uint32_t bit_offset = i * SEW;
        uint64_t vs2_val = reg_status->Vector_Register[vs2].range(bit_offset + SEW - 1, bit_offset).to_uint64();
        bool mask = reg_status->Vector_Register[0].range(bit_offset + SEW - 1, bit_offset).to_uint64() != 0;
        reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  (mask != 0) ? signed_imm: vs2_val;
    }

    printf("\n\n_______________________\n\n");
}


void vmsne_vv(Register_Status* reg_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {
    printf("\033[34m\nvmsne.vv  v%d.mask[i] = v%d[i] != v%d[i] ? 1 : 0 \n\033[0m", vd, vs2, vs1);


    int SEW = reg_status->vtype.SEW;
    uint32_t VL = reg_status->VL;

    for (uint32_t i = 0; i < VL; i++) {
        uint32_t bit_offset = i * SEW;

        uint64_t vs2_val = reg_status->Vector_Register[vs2].range(bit_offset + SEW - 1, bit_offset).to_uint64();
        uint64_t vs1_val = reg_status->Vector_Register[vs1].range(bit_offset + SEW - 1, bit_offset).to_uint64();

        bool mask = reg_status->Vector_Register[0].range(bit_offset + SEW - 1, bit_offset).to_uint64() != 0;

        if(vm == 1){ // here we process all elements up to vl
            reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  (vs2_val != vs1_val) ? 1: 0;
        }
        else{ // here we process only elements where v0.mask[i] = 1
            if (mask){
                reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  (vs2_val != vs1_val) ? 1: 0;
            }
            else{
                reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  0; // (agnostic policy for masked-out elements).
            }
        }

    }

    printf("\n\n_______________________\n\n");
}


void vmseq_vi(Register_Status* reg_status, uint8_t vd, uint8_t Imm, uint8_t vs2, uint8_t vm) {
    printf("\033[34m\nvmseq.vi: v%d.mask[i] = (v%d[i] == imm(%d)) ? 1 : 0 \n\033[0m", vd, vs2, Imm);

    int SEW = reg_status->vtype.SEW;
    uint32_t VL = reg_status->VL;

    int8_t imm5 = static_cast<int8_t>(Imm << 3) >> 3;  // Extract 5-bit signed value
    int64_t signed_imm = static_cast<int64_t>(imm5);     // Sign-extend to 64 bits
    uint64_t imm_unsigned = static_cast<uint64_t>(signed_imm) & ((1ULL << SEW) - 1);

    for (uint32_t i = 0; i < VL; i++) {
        uint32_t bit_offset = i * SEW;

        uint64_t vs2_val = reg_status->Vector_Register[vs2].range(bit_offset + SEW - 1, bit_offset).to_uint64();

        bool mask = reg_status->Vector_Register[0].range(bit_offset + SEW - 1, bit_offset).to_uint64() != 0;

        if(vm == 1){ // here we process all elements up to vl
            reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  (vs2_val == imm_unsigned) ? 1: 0;
        }
        else{ // here we process only elements where v0.mask[i] = 1
            if (mask){
                reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  (vs2_val == imm_unsigned) ? 1: 0;
            }
            else{
                reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  0; // (agnostic policy for masked-out elements).
            }
        }
    }

    printf("\n\n_______________________\n\n");
}


void vmsne_vi(Register_Status* reg_status, uint8_t vd, uint8_t Imm, uint8_t vs2, uint8_t vm) {
    printf("\033[34m\nvmsne.vi: v%d.mask[i] = (v%d[i] != imm(%d)) ? 1 : 0 \n\033[0m", vd, vs2, Imm);

    int SEW = reg_status->vtype.SEW;
    uint32_t VL = reg_status->VL;

    int8_t imm5 = static_cast<int8_t>(Imm << 3) >> 3;  // Extract 5-bit signed value
    int64_t signed_imm = static_cast<int64_t>(imm5);     // Sign-extend to 64 bits

    for (uint32_t i = 0; i < VL; i++) {
        uint32_t bit_offset = i * SEW;

        uint64_t vs2_val = reg_status->Vector_Register[vs2].range(bit_offset + SEW - 1, bit_offset).to_uint64();

        bool mask = reg_status->Vector_Register[0].range(bit_offset + SEW - 1, bit_offset).to_uint64() != 0;

        if(vm == 1){ // here we process all elements up to vl
            reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  (vs2_val != signed_imm) ? 1: 0;
        }
        else{ // here we process only elements where v0.mask[i] = 1
            if (mask){
                reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  (vs2_val != signed_imm) ? 1: 0;
            }
            else{
                reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  0; // (agnostic policy for masked-out elements).
            }
        }
    }

    printf("\n\n_______________________\n\n");
}


void vmsltu_vv(Register_Status* reg_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {
    printf("\033[34m\nvmsltu.vv  v%d.mask[i] = v%d[i] < v%d[i] ? 1 : 0 (Unsigned)\n\033[0m", vd, vs2, vs1);


    int SEW = reg_status->vtype.SEW;
    uint32_t VL = reg_status->VL;

    for (uint32_t i = 0; i < VL; i++) {
        uint32_t bit_offset = i * SEW;

        uint64_t vs2_val = reg_status->Vector_Register[vs2].range(bit_offset + SEW - 1, bit_offset).to_uint64();
        uint64_t vs1_val = reg_status->Vector_Register[vs1].range(bit_offset + SEW - 1, bit_offset).to_uint64();

        bool mask = reg_status->Vector_Register[0].range(bit_offset + SEW - 1, bit_offset).to_uint64() != 0;

        if(vm == 1){ // masking disabled, here we process all elements up to vl
            reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  (vs2_val < vs1_val) ? 1: 0;
        }
        else{ // masking enabled, here we process only elements where v0.mask[i] = 1
            if (mask){
                reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  (vs2_val < vs1_val) ? 1: 0;
            }
            else{
                reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  0; // (agnostic policy for masked-out elements).
            }
        }

    }

    printf("\n\n_______________________\n\n");
}


void vmslt_vv(Register_Status* reg_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {
    printf("\033[34m\nvmslt.vv  v%d.mask[i] = v%d[i] < v%d[i] ? 1 : 0 (Signed)\n\033[0m", vd, vs2, vs1);


    int SEW = reg_status->vtype.SEW;
    uint32_t VL = reg_status->VL;

    for (uint32_t i = 0; i < VL; i++) {
        uint32_t bit_offset = i * SEW;

        int64_t vs2_val = reg_status->Vector_Register[vs2].range(bit_offset + SEW - 1, bit_offset).to_int64();
        int64_t vs1_val = reg_status->Vector_Register[vs1].range(bit_offset + SEW - 1, bit_offset).to_int64();

        bool mask = reg_status->Vector_Register[0].range(bit_offset + SEW - 1, bit_offset).to_uint64() != 0;

        if(vm == 1){ // masking disabled, here we process all elements up to vl
            reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  (vs2_val < vs1_val) ? 1: 0;
        }
        else{ // masking enabled, here we process only elements where v0.mask[i] = 1
            if (mask){
                reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  (vs2_val < vs1_val) ? 1: 0;
            }
            else{
                reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  0; // (agnostic policy for masked-out elements).
            }
        }

    }

    printf("\n\n_______________________\n\n");
}


void vmsleu_vv(Register_Status* reg_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {
    printf("\033[34m\nvmslteu.vv  v%d.mask[i] = v%d[i] <= v%d[i] ? 1 : 0 (Unsigned)\n\033[0m", vd, vs2, vs1);


    int SEW = reg_status->vtype.SEW;
    uint32_t VL = reg_status->VL;

    for (uint32_t i = 0; i < VL; i++) {
        uint32_t bit_offset = i * SEW;

        uint64_t vs2_val = reg_status->Vector_Register[vs2].range(bit_offset + SEW - 1, bit_offset).to_uint64();
        uint64_t vs1_val = reg_status->Vector_Register[vs1].range(bit_offset + SEW - 1, bit_offset).to_uint64();

        bool mask = reg_status->Vector_Register[0].range(bit_offset + SEW - 1, bit_offset).to_uint64() != 0;

        if(vm == 1){ // masking disabled, here we process all elements up to vl
            reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  (vs2_val <= vs1_val) ? 1: 0;
        }
        else{ // masking enabled, here we process only elements where v0.mask[i] = 1
            if (mask){
                reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  (vs2_val <= vs1_val) ? 1: 0;
            }
            else{
                reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  0; // (agnostic policy for masked-out elements).
            }
        }

    }

    printf("\n\n_______________________\n\n");
}


void vmsleu_vi(Register_Status* reg_status, uint8_t vd, uint8_t Imm, uint8_t vs2, uint8_t vm) {
    printf("\033[34m\nvmsleu.vi: v%d.mask[i] = (v%d[i] <= imm(%d)) ? 1 : 0 (Unsigned)\n\033[0m", vd, vs2, Imm);

    int SEW = reg_status->vtype.SEW;
    uint32_t VL = reg_status->VL;

    int8_t imm5 = static_cast<int8_t>(Imm << 3) >> 3;  // Extract 5-bit signed value
    int64_t signed_imm = static_cast<int64_t>(imm5);     // Sign-extend to 64 bits
    uint64_t imm_unsigned = static_cast<uint64_t>(signed_imm) & ((1ULL << SEW) - 1);

    for (uint32_t i = 0; i < VL; i++) {
        uint32_t bit_offset = i * SEW;

        uint64_t vs2_val = reg_status->Vector_Register[vs2].range(bit_offset + SEW - 1, bit_offset).to_uint64();

        bool mask = reg_status->Vector_Register[0].range(bit_offset + SEW - 1, bit_offset).to_uint64() != 0;

        if(vm == 1){ // here we process all elements up to vl
            reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  (vs2_val <= imm_unsigned) ? 1: 0;
        }
        else{ // here we process only elements where v0.mask[i] = 1
            if (mask){
                reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  (vs2_val <= imm_unsigned) ? 1: 0;
            }
            else{
                reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  0; // (agnostic policy for masked-out elements).
            }
        }
    }

    printf("\n\n_______________________\n\n");
}


void vmsle_vv(Register_Status* reg_status, uint8_t vd, uint8_t vs1, uint8_t vs2, uint8_t vm) {
    printf("\033[34m\nvmslte.vv  v%d.mask[i] = v%d[i] <= v%d[i] ? 1 : 0 (Signed)\n\033[0m", vd, vs2, vs1);


    int SEW = reg_status->vtype.SEW;
    uint32_t VL = reg_status->VL;

    for (uint32_t i = 0; i < VL; i++) {
        uint32_t bit_offset = i * SEW;

        int64_t vs2_val = reg_status->Vector_Register[vs2].range(bit_offset + SEW - 1, bit_offset).to_int64();
        int64_t vs1_val = reg_status->Vector_Register[vs1].range(bit_offset + SEW - 1, bit_offset).to_int64();

        bool mask = reg_status->Vector_Register[0].range(bit_offset + SEW - 1, bit_offset).to_uint64() != 0;

        if(vm == 1){ // masking disabled, here we process all elements up to vl
            reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  (vs2_val <= vs1_val) ? 1: 0;
        }
        else{ // masking enabled, here we process only elements where v0.mask[i] = 1
            if (mask){
                reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  (vs2_val <= vs1_val) ? 1: 0;
            }
            else{
                reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  0; // (agnostic policy for masked-out elements).
            }
        }

    }

    printf("\n\n_______________________\n\n");
}


void vmsle_vi(Register_Status* reg_status, uint8_t vd, uint8_t Imm, uint8_t vs2, uint8_t vm) {
    printf("\033[34m\nvmsle.vi: v%d.mask[i] = (v%d[i] <= imm(%d)) ? 1 : 0 (Signed)\n\033[0m", vd, vs2, Imm);

    int SEW = reg_status->vtype.SEW;
    uint32_t VL = reg_status->VL;

    int8_t imm5 = static_cast<int8_t>(Imm << 3) >> 3;  // Extract 5-bit signed value
    int64_t signed_imm = static_cast<int64_t>(imm5);     // Sign-extend to 64 bits

    for (uint32_t i = 0; i < VL; i++) {
        uint32_t bit_offset = i * SEW;

        int64_t vs2_val = reg_status->Vector_Register[vs2].range(bit_offset + SEW - 1, bit_offset).to_int64();

        bool mask = reg_status->Vector_Register[0].range(bit_offset + SEW - 1, bit_offset).to_uint64() != 0;

        if(vm == 1){ // here we process all elements up to vl
            reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  (vs2_val <= signed_imm) ? 1: 0;
        }
        else{ // here we process only elements where v0.mask[i] = 1
            if (mask){
                reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  (vs2_val <= signed_imm) ? 1: 0;
            }
            else{
                reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  0; // (agnostic policy for masked-out elements).
            }
        }
    }

    printf("\n\n_______________________\n\n");
}


void vmsgtu_vi(Register_Status* reg_status, uint8_t vd, uint8_t Imm, uint8_t vs2, uint8_t vm) {
    printf("\033[34m\nvmsgtu.vi: v%d.mask[i] = (v%d[i] > imm(%d)) ? 1 : 0 (Unsigned)\n\033[0m", vd, vs2, Imm);

    int SEW = reg_status->vtype.SEW;
    uint32_t VL = reg_status->VL;

    int8_t imm5 = static_cast<int8_t>(Imm << 3) >> 3;  // Extract 5-bit signed value
    int64_t signed_imm = static_cast<int64_t>(imm5);     // Sign-extend to 64 bits
    uint64_t imm_unsigned = static_cast<uint64_t>(signed_imm) & ((1ULL << SEW) - 1);

    for (uint32_t i = 0; i < VL; i++) {
        uint32_t bit_offset = i * SEW;

        uint64_t vs2_val = reg_status->Vector_Register[vs2].range(bit_offset + SEW - 1, bit_offset).to_uint64();

        bool mask = reg_status->Vector_Register[0].range(bit_offset + SEW - 1, bit_offset).to_uint64() != 0;

        if(vm == 1){ // here we process all elements up to vl
            reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  (vs2_val > imm_unsigned) ? 1: 0;
        }
        else{ // here we process only elements where v0.mask[i] = 1
            if (mask){
                reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  (vs2_val > imm_unsigned) ? 1: 0;
            }
            else{
                reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  0; // (agnostic policy for masked-out elements).
            }
        }
    }

    printf("\n\n_______________________\n\n");
}


void vmsgt_vi(Register_Status* reg_status, uint8_t vd, uint8_t Imm, uint8_t vs2, uint8_t vm) {
    printf("\033[34m\nvmsgt.vi: v%d.mask[i] = (v%d[i] > imm(%d)) ? 1 : 0 (Signed)\n\033[0m", vd, vs2, Imm);

    int SEW = reg_status->vtype.SEW;
    uint32_t VL = reg_status->VL;

    int8_t imm5 = static_cast<int8_t>(Imm << 3) >> 3;  // Extract 5-bit signed value
    int64_t signed_imm = static_cast<int64_t>(imm5);     // Sign-extend to 64 bits

    for (uint32_t i = 0; i < VL; i++) {
        uint32_t bit_offset = i * SEW;

        int64_t vs2_val = reg_status->Vector_Register[vs2].range(bit_offset + SEW - 1, bit_offset).to_int64();

        bool mask = reg_status->Vector_Register[0].range(bit_offset + SEW - 1, bit_offset).to_uint64() != 0;

        if(vm == 1){ // here we process all elements up to vl
            reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  (vs2_val > signed_imm) ? 1: 0;
        }
        else{ // here we process only elements where v0.mask[i] = 1
            if (mask){
                reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  (vs2_val > signed_imm) ? 1: 0;
            }
            else{
                reg_status->Vector_Register[vd].range(bit_offset + SEW - 1, bit_offset) =  0; // (agnostic policy for masked-out elements).
            }
        }
    }

    printf("\n\n_______________________\n\n");
}