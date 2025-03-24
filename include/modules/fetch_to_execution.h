#ifndef FETCH_TO_EXECUTION_H
#define FETCH_TO_EXECUTION_H

#include <systemc.h>
#include "instruction_fetch_stage.h"
#include "decode_execution_stage.h"

SC_MODULE(Fetch_To_Execution) {
    Instruction_Fetch_Stage fetch;
    Decode_Execution_Stage decode;
    sc_signal<sc_bv<32>> instruction_sig;  // Signal to connect ports

    SC_CTOR(Fetch_To_Execution) : fetch("fetch"), decode("decode") {
        // Connect fetch's output to the signal
        fetch.instruction_out(instruction_sig);
        // Connect the signal to decode's input
        decode.instruction(instruction_sig);
    }
};

#endif