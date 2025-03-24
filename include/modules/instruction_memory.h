#ifndef INSTRUCTION_MEMORY_H
#define INSTRUCTION_MEMORY_H

#include <systemc.h>
#include <fstream>
#include "include/register_types.h"
/////               INSTRUCTION MEMORY MODULE           //////////

SC_MODULE(Instruction_Memory) {
    sc_in<sc_uint<8>> address;
    sc_out<sc_bv<32>> instruction;


    const std::string filePath = "files/instructions.bin";

    void read_from_rom() {
        instruction.write(memory[address.read()]);
        //Decode
    }

    void load_memory() {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Error: Cannot open file " << filePath << std::endl;
            sc_stop();
            return;
        }

        std::string line;
        int i = 0;
        while (std::getline(file, line) && i < INSTRUCTION_MEMORY_SIZE ) {
            if (line.length() != 32) {
                std::cerr << "Invalid instruction length at line " << i << std::endl;
                continue;
            }
          
            memory[i] = sc_bv<32>(line.c_str());
            
            i++;
        }

     
        file.close();
    }
    


    SC_CTOR(Instruction_Memory){
        load_memory();  // Load instructions from input file

        SC_METHOD(read_from_rom);

        sensitive << address;
    }
};

#endif