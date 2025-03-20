#ifndef Instruction_Fetch_H
#define Instruction_Fetch_H

#include <systemc.h>

SC_MODULE(Instruction_Memory) {
    sc_in<sc_uint<8>> address;
    sc_out<sc_bv<32>> instruction;

    sc_bv<32> memory[256];  // 256 x 32-bit memory

    const std::string filePath = "instructions.bin";

    void read_from_rom() {
        instruction.write(memory[address.read()]);
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
        while (std::getline(file, line) && i < 256) {
            if (line.length() != 32) {
                std::cerr << "Invalid instruction length at line " << i << std::endl;
                continue;
            }
            memory[i] = sc_bv<32>(line.c_str());
            
            i++;
        }

     
        file.close();
    }

    SC_CTOR(Instruction_Memory) {
        load_memory();  // Load instructions from input file

        SC_METHOD(read_from_rom);
        sensitive << address;
    }
};


SC_MODULE(Instruction_Fetch_Stage){
   

    sc_out<sc_bv<32>> instruction_out;


    Instruction_Memory instruction_memory_instance;

    sc_signal <sc_uint<8>> PC; //wire

    SC_CTOR(Instruction_Fetch_Stage) : instruction_memory_instance("im"){
        instruction_memory_instance.address(PC);
        instruction_memory_instance.instruction(instruction_out);

        PC.write(0); // intialize the pc with value 0


        SC_THREAD(fetch);
        
    }
    void fetch(){
        
        while (true)
        {
            wait(1,SC_NS);
            if(PC.read() == 39){
                sc_stop();
                break;
            }
            PC.write(PC.read() + 1);
        }
   
    }
    void reset_pc(){
        PC.write(0);
    }                                                                          
};




#endif 