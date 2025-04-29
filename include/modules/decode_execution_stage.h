#ifndef DECODE_EXECUTION_STAGE_H
#define DECODE_EXECUTION_STAGE_H
#include <systemc.h>
#include "register_types.h"
#include "instructions.h"

////////////////                       DECODE AND EXECUTION STAGE                        //////////////////

SC_MODULE(Decode_Execution_Stage) {
    sc_in<sc_bv<32>> instruction;
    bool first_instruction;  // Flag to skip the first reading instution "Zeros"

    sc_bv<32> instruction_div;    /// for takes the value of instrution to split 

    sc_bv<6> funct6;
    sc_bv<1> vm;
    unsigned int vs2;
    unsigned int vs1;
    sc_bv<3> funct3;
    unsigned int vd;
    sc_bv<7> opcode;
    SC_CTOR(Decode_Execution_Stage) : first_instruction(true) {
        SC_METHOD(decode_process);
        sensitive << instruction;  // Trigger on instruction changes
    }

    void decode_process() {
        if (first_instruction) {
            first_instruction = false; 
            return;
        }

        instruction_div = instruction.read();
        funct6 = instruction_div.range(31,26);
        vm = instruction_div.range(25,25);
        vs2 = instruction_div.range(24,20).to_uint();           //convert from string to unsigned int 
        vs1 = instruction_div.range(19,15).to_uint();
        funct3 = instruction_div.range(14,12);
        vd = instruction_div.range(11,7).to_uint();
        opcode = instruction_div.range(6,0);

        switch(opcode.to_uint()){
            case 0b1010111: 
                switch (funct6.to_uint()){
                 
                    case 0b000000:                                  // Vadd or vredsums

                        switch (funct3.to_uint()){     
                            case 0b000:{                              // Vector to Vector (vadd.vv)
                                    vadd_vv(reg_status,vd,vs1,vs2,vm.to_uint());
                                    break;}
                            case 0b011:{                              // Vector to Immediate(vadd.vi)
                                    int8_t Imm=instruction_div.range(19,15).to_int();
                                    vadd_vi(reg_status,vd,vs2,Imm,vm.to_uint());
                                    break;}
                            case 0b010:{                              // Vector to Vector(vredsum_vs)
                                    vredsum_vs(reg_status,vd,vs2,vs1,vm.to_uint());
                                    break;}
                        }break;

                    case 0b000001:                                    // vredand

                        switch (funct3.to_uint()){ 
                            case 0b010:{                              // Vector to Vector (vredand.vs)
                                    vredand_vs(reg_status,vd,vs2,vs1,vm.to_uint());  
                                    break;}
                        }break;
                    
                        
                    case 0b000010:                                  //Vsub

                        switch (funct3.to_uint()){ 
                            case 0b000:{                              // Vector to Vector 
                                    vsub_vv(reg_status,vd,vs1,vs2,vm.to_uint());  
                                    break;}
                            case 0b010:{                              // Vector to Vector (vredor.vs)
                                    vredor_vs(reg_status,vd,vs2,vs1,vm.to_uint());  
                                    break;}
                        }break;

                    case 0b000011:                                  //Vrsub or Vredxor

                        switch (funct3.to_uint()){ 
                            case 0b011:{                              // Vector to Immediate (vrsub.vi)
                                    int8_t Imm=instruction_div.range(19,15).to_int();
                                    vrsub_vi(reg_status,vd,vs2,Imm,vm.to_uint()); 
                                    break;}
                            case 0b010:{                              // Vector to Vector (vredxor.vs)
                                    vredxor_vs(reg_status,vd,vs2,vs1,vm.to_uint()); 
                                    break;}
                        }break;

                    case 0b001001:                                  //Vand or vaadd

                    switch (funct3.to_uint()){ 
                        case 0b000:{                                 // Vector to Vector (vand.vv)
                                vand_vv(reg_status,vd,vs1,vs2,vm.to_uint()); 
                                break;}
                        case 0b011:{                                 // Vector to Immediate (vand.vi)
                                int8_t Imm=instruction_div.range(19,15).to_int();
                                vand_vi(reg_status,vd,vs2,Imm,vm.to_uint()); 
                                break;}    
                        case 0b010:{                                 // Vector to Vector (vaadd.vv)
                                vaadd_vv(reg_status,vd,vs2,vs1,vm.to_uint()); 
                                break;}  
                    }break;

                    case 0b001010:                                  //Vor or Vasubu

                    switch (funct3.to_uint()){ 
                        case 0b000:{                                 // Vector to Vector (vor.vv)
                                vor_vv(reg_status,vd,vs1,vs2,vm.to_uint()); 
                                break;}
                        case 0b011:{                                 // Vector to Immediate (vor.vi)
                                int8_t Imm=instruction_div.range(19,15).to_int();
                                vor_vi(reg_status,vd,vs2,Imm,vm.to_uint()); 
                                break;} 
                        case 0b010:{                                 // Vector to Vector (vasubu.vv)
                                vasubu_vv(reg_status,vd,vs2,vs1,vm.to_uint()); 
                                break;}    
                    }break;

                    case 0b001011:                                   //Vxor or Vasub

                    switch (funct3.to_uint()){ 
                        case 0b000:{                                 // Vector to Vector (vxor.vv)
                                vxor_vv(reg_status,vd,vs1,vs2,vm.to_uint()); 
                                break;}
                        case 0b011:{                                // Vector to Immediate(vxor.vi)
                                int8_t Imm=instruction_div.range(19,15).to_int();
                                vxor_vi(reg_status,vd,vs2,Imm,vm.to_uint());
                                break;}
                        case 0b010:{                                // Vector to Vector(vasub.vv)
                                vasub_vv(reg_status,vd,vs2,vs1,vm.to_uint());
                                break;}
                    }break;

                    case 0b010111:                                    //VMV

                    switch (funct3.to_uint()){ 
                        case 0b000:                                  // Vector to Vector (vmv.v.v)
                        if (vs2 == 0){
                            vmv_v_v(reg_status,vd,vs1,vm.to_uint()); 
                            break;
                        }
                        else{                                        // Vector to Vector (vmerge.vvm)
                            vmerge_vvm(reg_status,vd,vs1,vs2,vm.to_uint()); 
                            break;
                        }
                        case 0b011:                                  // Vector to Immediate(vmv.v.i)
                        if (vs2 == 0){
                            int8_t Imm=instruction_div.range(19,15).to_int();
                            vmv_v_i(reg_status,vd,Imm,vm.to_uint());
                            break;
                        }
                        else{                                       // Vector to Immediate (vmerge.vim)
                            vmerge_vim(reg_status,vd,instruction_div.range(19,15).to_int(),vs2,vm.to_uint());
                            break;
                        }
                    }break;

                    case 0b001000:                                   //Vaaddu

                    switch (funct3.to_uint()){ 
                        case 0b010:{                                // Vector to Vector(vaaddu.vv)
                                vaaddu_vv(reg_status,vd,vs2,vs1,vm.to_uint());
                                break;}
                    }break;

                    case 0b000101:                                  //vmin or vredmin

                    switch (funct3.to_uint()){ 
                        case 0b000:{                                 // Vector to Vector (vmin.vv)
                                vmin_vv(reg_status,vd,vs1,vs2,vm.to_uint()); 
                                break;}
                        case 0b010:{                                 // Vector to Vector (vredmin.vs)
                                vredmin_vs(reg_status,vd,vs2,vs1,vm.to_uint()); 
                                break;}
                    }break;

                    case 0b000111:                                  //vmax or vredmax

                    switch (funct3.to_uint()){ 
                        case 0b000:{                                 // Vector to Vector (vmax.vv)
                                vmax_vv(reg_status,vd,vs1,vs2,vm.to_uint()); 
                                break;}
                        case 0b010:{                                 // Vector to Vector (vredmax.vs)
                                vredmax_vs(reg_status,vd,vs2,vs1,vm.to_uint()); 
                                break;}
                    }break;

                    case 0b000100:                                  //vminu or vredminu

                    switch (funct3.to_uint()){ 
                        case 0b000:{                                 // Vector to Vector (vminu.vv)
                                vminu_vv(reg_status,vd,vs1,vs2,vm.to_uint()); 
                                break;}
                        case 0b010:{                                 // Vector to Vector (vredminu.vs)
                                vredminu_vs(reg_status,vd,vs2,vs1,vm.to_uint()); 
                                break;}

                    }break;

                    case 0b000110:                                  //vmaxu or vredmaxu

                    switch (funct3.to_uint()){ 
                        case 0b000:{                                 // Vector to Vector (vmaxu.vv)
                                vmaxu_vv(reg_status,vd,vs1,vs2,vm.to_uint()); 
                                break;}
                        case 0b010:{                                 // Vector to Vector (vredmaxu.vs)
                                vredmaxu_vs(reg_status,vd,vs2,vs1,vm.to_uint()); 
                                break;}
                    }break;

                    case 0b001100:                                  //VRGATHER

                    switch (funct3.to_uint()){ 
                        case 0b000:                                 // Vector to Vector (vrgather.vv)
                                vrgather_vv(reg_status,vd,vs1,vs2,vm.to_uint()); 
                                break;
                        case 0b011:                                 // Vector to Immediate (vrgather.vi)
                                uint8_t Imm = instruction_div.range(19,15).to_uint();
                                vrgather_vi(reg_status,vd,vs2,Imm,vm.to_uint()); 
                                break;
                    }break;
                    

                    case 0b001110:                                  //VRGATHEREI16

                    switch (funct3.to_uint()){ 
                        case 0b000:                                 // Vector to Vector (vrgatherei16.vv)
                                vrgatherei16_vv(reg_status,vd,vs1,vs2,vm.to_uint()); 
                                break;
                        case 0b011:                                 // Vector to Immediate (vslideup.vi )
                                uint8_t Imm = instruction_div.range(19,15).to_uint();
                                vslideup_vi(reg_status,vd,vs2,Imm,vm.to_uint()); 
                                break;
                    }break;


                    case 0b001111:                                  //VSLIDEDOWN_VI

                    switch (funct3.to_uint()){ 
                        case 0b011:                                 // Vector to Immediate (vslidedown.vi )
                                uint8_t Imm = instruction_div.range(19,15).to_uint();
                                vslidedown_vi(reg_status,vd,vs2,Imm,vm.to_uint()); 
                                break;
                    }break;


                    case 0b100000:                                  //VSADDU

                    switch (funct3.to_uint()){ 
                        case 0b000:                                 // Vector to Vector (vsaddu.vv)
                                vsaddu_vv(reg_status,vd,vs1,vs2,vm.to_uint()); 
                                break;
                        case 0b011:                                 // Vector to Immedaite (vsaddu.vi)
                                uint8_t Imm = instruction_div.range(19,15).to_uint();
                                vsaddu_vi(reg_status,vd,vs2,Imm,vm.to_uint()); 
                                break;
                    }break;

                    case 0b100001:                                  //VSADD

                    switch (funct3.to_uint()){ 
                        case 0b000:                                 // Vector to Vector (vsadd.vv)
                                vsadd_vv(reg_status,vd,vs1,vs2,vm.to_uint()); 
                                break;
                        case 0b011:                                 // Vector to Immediate (vsadd.vi)
                                int8_t Imm = instruction_div.range(19,15).to_int();
                                vsadd_vi(reg_status,vd,vs2,Imm,vm.to_uint()); 
                                break;
                    }break;


                    case 0b100010:                                  //VSSUBU

                    switch (funct3.to_uint()){ 
                        case 0b000:                                 // Vector to Vector (vssubu.vv)
                                vssubu_vv(reg_status,vd,vs1,vs2,vm.to_uint()); 
                                break;
                    }break;

                    case 0b100011:                                  //VSSUB

                    switch (funct3.to_uint()){ 
                        case 0b000:                                 // Vector to Vector (vssub.vv)
                                vssub_vv(reg_status,vd,vs1,vs2,vm.to_uint()); 
                                break;
                    }break;

                    case 0b100101:                                  //VSLL

                    switch (funct3.to_uint()){ 
                        case 0b000:                                 // Vector to Vector (vsll.vv)
                                vsll_vv(reg_status,vd,vs1,vs2,vm.to_uint()); 
                                break;
                        case 0b011:    
                                uint8_t Imm = instruction_div.range(19,15).to_uint();    // Vector to Immediate (vsll.vi)
                                vsll_vi(reg_status,vd,vs2,Imm,vm.to_uint()); 
                                break;
                    }break;


                    case 0b101000:                                  //VSRL

                    switch (funct3.to_uint()){ 
                        case 0b000:                                 // Vector to Vector (vsrl.vv)
                                vsrl_vv(reg_status,vd,vs1,vs2,vm.to_uint()); 
                                break;
                        case 0b011:                                 // Vector to Immediate (vsrl.vi)
                                uint8_t Imm = instruction_div.range(19,15).to_uint();  
                                vsrl_vi(reg_status,vd,vs2,Imm,vm.to_uint()); 
                                break;
                    }break;


                    case 0b100111:                                  //VSMUL

                    switch (funct3.to_uint()){ 
                        case 0b000:                                 // Vector to Vector (vsmul.vv)
                                vsmul_vv(reg_status,vd,vs1,vs2,vm.to_uint()); 
                                break;
                    }break;
                    

                    case 0b101001:                                  //VSRA

                    switch (funct3.to_uint()){ 
                        case 0b000:                                 // Vector to Vector (vsra.vv)
                                vsra_vv(reg_status,vd,vs1,vs2,vm.to_uint()); 
                                break;
                        case 0b011:                                 // Vector to Immediate (vsra.vi)
                                uint8_t Imm = instruction_div.range(19,15).to_uint();  
                                vsra_vi(reg_status,vd,vs2,Imm,vm.to_uint()); 
                                break;
                    }break;

                    case 0b010000:                                  //vadc.vvm

                    switch (funct3.to_uint()){
                        case 0b000:                                 // Vector to Vector (vadc.vvm ) with  carry-in
                                vadc_vvm(reg_status,vd,vs1,vs2,vm.to_uint());
                                break;
                        case 0b011:                                 // Vector to sign_extended imm (vadc.vvm ) with  carry-in
                                vadc_vim(reg_status,vd,instruction_div.range(19,15).to_int(),vs2,vm.to_uint());
                                break;    
                    }break;

                    case 0b010001:                                  //vmadc.vvm

                    switch (funct3.to_uint()){
                        case 0b000:                                 // Vector to Vector (vmadc.vvm ) with  carry-in
                                vmadc_vvm(reg_status,vd,vs1,vs2,vm.to_uint());
                                break;
                        case 0b011:                                 // Vector to sign_extended imm (vmadc.vim ) with  carry-in / (vmadc.vi) wuithout carry-in
                                vmadc_vi(reg_status,vd,instruction_div.range(19,15).to_int(),vs2,vm.to_uint());
                                break;
                    }break;

                    case 0b010010:                                  //vsbc.vvm

                    switch (funct3.to_uint()){
                        case 0b000:                                 // Vector to Vector (vsbc.vvm ) with  carry-in
                                vsbc_vvm(reg_status,vd,vs1,vs2,vm.to_uint());
                                break;
                    }break;

                    case 0b010011:                                  //vmsbc.vv and vmsbc.vvm

                    switch (funct3.to_uint()){
                        case 0b000:                                 // Vector to Vector (vmsbc.vv and .vvm ) with/without  carry-in
                                vmsbc_vv(reg_status,vd,vs1,vs2,vm.to_uint());
                                break;
                    }break;

                    case 0b011001:                                  //vmsne.vv

                    switch (funct3.to_uint()){
                        case 0b000:                                 // Vector to Vector (vmsne.vv)
                                vmsne_vv(reg_status,vd,vs1,vs2,vm.to_uint());
                                break;
                        case 0b011:                                 // Vector to Immediate (vmsne.vi)
                                vmsne_vi(reg_status,vd,instruction_div.range(19,15).to_int(),vs2,vm.to_uint());
                                break;
                    }break;

                    case 0b011000:                                  //vmseq.vi

                    switch (funct3.to_uint()){
                        case 0b011:                                 // Vector to Vector (vmsne.vv)
                                vmseq_vi(reg_status,vd,instruction_div.range(19,15).to_int(),vs2,vm.to_uint());
                                break;
                    }break;

                    case 0b011010:                                  //vmsltu.vv

                    switch (funct3.to_uint()){
                        case 0b000:                                 // Vector to Vector (vmsltu.vv)
                                vmsltu_vv(reg_status,vd,vs1,vs2,vm.to_uint());
                                break;
                    }break;

                    case 0b011011:                                  //vmslt.vv

                    switch (funct3.to_uint()){
                        case 0b000:                                 // Vector to Vector (vmslt.vv)
                                vmslt_vv(reg_status,vd,vs1,vs2,vm.to_uint());
                                break;
                    }break;

                    case 0b011100:                                  //vmslteu.vv

                    switch (funct3.to_uint()){
                        case 0b000:                                 // Vector to Vector (vmsleu.vv)
                                vmsleu_vv(reg_status,vd,vs1,vs2,vm.to_uint());
                                break;
                        case 0b011:                                 // Vector to Immediate (vmsleu.vi)
                                vmsleu_vi(reg_status,vd,instruction_div.range(19,15).to_int(),vs2,vm.to_uint());
                                break;
                    }break;

                    case 0b011101:                                  //vmsle.vv

                    switch (funct3.to_uint()){
                        case 0b000:                                 // Vector to Vector (vmsle.vv)
                                vmsle_vv(reg_status,vd,vs1,vs2,vm.to_uint());
                                break;
                        case 0b011:                                 // Vector to Immediate (vmsle.vi)
                                vmsle_vi(reg_status,vd,instruction_div.range(19,15).to_int(),vs2,vm.to_uint());
                                break;
                    }break;

                    case 0b011110:                                  //vmsgtu.vi

                    switch (funct3.to_uint()){
                        case 0b011:                                 // Vector to Immediate (vmsgtu.vi)
                                vmsgtu_vi(reg_status,vd,instruction_div.range(19,15).to_int(),vs2,vm.to_uint());
                                break;
                    }break;

                    case 0b011111:                                  //vmsgt.vi

                    switch (funct3.to_uint()){
                        case 0b011:                                 // Vector to Immediate (vmsgt.vi)
                                vmsgt_vi(reg_status,vd,instruction_div.range(19,15).to_int(),vs2,vm.to_uint());
                                break;
                    }break;
                    
                    case 0b101010:                                  //vssrl

                    switch (funct3.to_uint()){
                        case 0b000:                                 // Vector to Vector (vssrl.vv)
                                vssrl_vv(reg_status,vd,vs2,vs1,vm.to_uint());
                                break;
                        case 0b011:                                 // Vector to Immediate (vssrl.vi)
                                uint8_t Imm = instruction_div.range(19,15).to_uint(); 
                                vssrl_vi(reg_status,vd,vs2,Imm,vm.to_uint());
                                break;
                    }break;

                    case 0b101011:                                  //vssra

                    switch (funct3.to_uint()){
                        case 0b000:                                 // Vector to Vector (vssra.vv)
                                vssra_vv(reg_status,vd,vs2,vs1,vm.to_uint());
                                break;
                        case 0b011:                                 // Vector to Immediate (vssra.vi)
                                uint8_t Imm = instruction_div.range(19,15).to_uint(); 
                                vssra_vi(reg_status,vd,vs2,Imm,vm.to_uint());
                                break;
                    }break;
                    
                    
                }
            break;

        case  0b1110011:{                                                                  //All CSR/system ops.
                sc_bv<12> CSR= instruction_div.range(31,20);
                switch (CSR.to_uint64()){
                        
                        case 0b000000001010:                                              // vxrm
                                switch (funct3.to_uint()){
                                        case 0b101:                                       // CSRRWI.
                                                if(vd==0){
                                                        sc_bv<5> Imm_bits = instruction_div.range(19,15);
                                                        csrwi_vxrm(reg_status,Imm_bits);      //Imm_bits represents the rounding mode (0...3) 
                                                } else{}                      
                                                break;
                                }break;  
                                
                        }

        }
        break;

        }
    
    }
};

#endif