#ifndef DECODE_EXECUTION_STAGE_H
#define DECODE_EXECUTION_STAGE_H

#include <systemc.h>
#include "include/register_types.h"
#include "include/instructions.h"

///////////             DECODE AND EXECUTION STAGE          ///////////////

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
        std::cout <<"Instruction:"<< instruction_div<<endl;
        funct6 = instruction_div.range(31,26);
        vm = instruction_div.range(25,25);
        vs2 = instruction_div.range(24,20).to_uint();           //convert from string to unsigned int 
        vs1 = instruction_div.range(19,15).to_uint();
        funct3 = instruction_div.range(14,12);
        vd = instruction_div.range(11,7).to_uint();
        opcode = instruction_div.range(6,0);
        int8_t Imm;

        switch(opcode.to_uint()){
            case 0b1010111: 
                switch (funct6.to_uint()){
                 
                    case 0b000000:                                  // Vadd

                        switch (funct3.to_uint()){     
                            case 0b000:                              // Vector to Vector (vadd.vv)
                                    vadd_vv(reg_status,vd,vs1,vs2,vm.to_uint());
                                    break;
                            case 0b011:                              // Vector to Immediate(vadd.vi)
                                    Imm=instruction_div.range(19,15).to_int();
                                    vadd_vi(reg_status,vd,vs2,Imm,vm.to_uint());
                                    break;
                        }break;
                    
                    case 0b000010:                                  //Vsub

                        switch (funct3.to_uint()){ 
                            case 0b000:                              // Vector to Vector 
                                    vsub_vv(reg_status,vd,vs1,vs2,vm.to_uint());  
                                    break;
                        }break;

                    case 0b000011:                                  //Vrsub

                        switch (funct3.to_uint()){ 
                            case 0b011:                              // Vector to Immediate (vrsub.vi)
                                    Imm=instruction_div.range(19,15).to_int();
                                    vrsub_vi(reg_status,vd,vs2,Imm,vm.to_uint()); 
                                    break;
                        }break;

                    case 0b001001:                                  //Vand

                    switch (funct3.to_uint()){ 
                        case 0b000:                                 // Vector to Vector (vand.vv)
                                vand_vv(reg_status,vd,vs1,vs2,vm.to_uint()); 
                                break;
                    }break;

                    case 0b001010:                                  //Vor

                    switch (funct3.to_uint()){ 
                        case 0b000:                                 // Vector to Vector (vor.vv)
                                vor_vv(reg_status,vd,vs1,vs2,vm.to_uint()); 
                                break;
                    }break;

                    case 0b001011:                                   //Vxor

                    switch (funct3.to_uint()){ 
                        case 0b000:                                 // Vector to Vector (vxor.vv)
                                vxor_vv(reg_status,vd,vs1,vs2,vm.to_uint()); 
                                break;
                        case 0b011:                                // Vector to Immediate(vxor.vi)
                                Imm=instruction_div.range(19,15).to_int();
                                // vxor_vi(reg_status,vd,vs2,Imm,vm.to_uint());
                                break;
                    }break;

                    case 0b010111:                                    //VMV

                    switch (funct3.to_uint()){ 
                        case 0b000:                                  // Vector to Vector (vmv.v.v)
                                // vmv_v_v(reg_status,vd,vs1,vm.to_uint()); 
                                break;
                        case 0b011:                                  // Vector to Immediate(vmv.v.i)
                                Imm=instruction_div.range(19,15).to_int();
                                // vxor_vi(reg_status,vd,vs2,Imm,vm.to_uint());
                                break;
                    }break;
                           
                    
                }
            break;
        }
    
        
         std::cout << "OPCODE: " << opcode << endl;
         std::cout << "funct6: " << funct6 << endl;
         std::cout << "vs1: " << vs1 << endl;
         std::cout << "vs2: " << vs2 << endl;
         std::cout << "vd: " << vd << endl;
        
        printf("\n\n\n");
    }
};

#endif