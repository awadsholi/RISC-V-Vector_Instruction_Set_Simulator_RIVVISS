#ifndef INSTRUCTION_FETCH_STAGE_H
#define INSTRUCTION_FETCH_STAGE_H

#include <systemc.h>
#include "instruction_memory.h"

///                 FETCH STAGE         ////////////////


SC_MODULE(Instruction_Fetch_Stage) {
    sc_out<sc_bv<32>> instruction_out;
    Instruction_Memory instruction_memory_instance;
    sc_signal<sc_uint<8>> PC;

    SC_CTOR(Instruction_Fetch_Stage) 
      : instruction_memory_instance("im")
    {
        instruction_memory_instance.address(PC);
        instruction_memory_instance.instruction(instruction_out);
        PC.write(0);
        SC_THREAD(fetch);
    }

    void fetch() {
        wait(SC_ZERO_TIME);  // Let initial instruction propagate

        while(true) {
            sc_uint<8> current_pc = PC.read();
            
            // Check exit condition
            if(current_pc == (INSTRUCTION_MEMORY_SIZE) - 1) {
                sc_stop();
                break;
            }

            // Increment PC and wait    sc_signal<sc_uint<8>> PC;

            PC.write(current_pc + 1);
            wait(1, SC_NS);
        }
    }

    void reset_pc() { PC.write(0); }
};

#endif