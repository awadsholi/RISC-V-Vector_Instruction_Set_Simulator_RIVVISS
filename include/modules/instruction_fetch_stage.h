#ifndef INSTRUCTION_FETCH_STAGE_H
#define INSTRUCTION_FETCH_STAGE_H

#include <systemc>
#include "instruction_memory.h"

SC_MODULE(Instruction_Fetch_Stage)
{
    sc_out<sc_bv<32>> instruction_out;                            // instruction output from fetch module
    Instruction_Memory imem;                                      // dynamic memory
    sc_signal<sc_uint<32>> PC;                                    // address 

    void fetch()                                                  // function for fetching instructions from Instruction memory
    {
        static bool stop_already_called = false;                 // to avoid calling sc_stop more than once
        wait(SC_ZERO_TIME);                                      // allowing the first value of PC assigned
        while (true) {
            if (PC.read() >= imem.size()) {                      // imem.size() is the number of available instructions
                if (!stop_already_called) {
                    stop_already_called = true;
                    sc_core::sc_stop();                          // Request SystemC to stop the simulation
                }
                return;                                          // terminate this thread
            }
            PC.write(PC.read() + 1);                             // increment PC to fetch the next PC
            wait(1, SC_NS);                                      // waiting 1 NS delay for fetching Instruction
        }
    }

    SC_CTOR(Instruction_Fetch_Stage)                                       
    : imem("imem")                                               // imem refer to Instruction_Memory module to be submodule defined (member initializer)
    {
        imem.address(PC);                                        // after initialize Instruction_Memory ,, assign value of PC as Address to imem (Input)
        imem.instruction(instruction_out);                       // assign instruction_out as Output from imem

        PC.write(0);                                             // first value of address assigned 0 ---> first value
        SC_THREAD(fetch);                                        // running the register process function (Combinationally,,SC_METHOD)
    }

    void reset_pc() { PC.write(0); }
};
#endif