// instruction_memory.h
#ifndef INSTRUCTION_MEMORY_H
#define INSTRUCTION_MEMORY_H

#include <systemc>
#include <fstream>
#include <vector>
#include "register_types.h"

SC_MODULE(Instruction_Memory)
{
    // ──────────────────────────DEFINE INPUTS AND OUTPUTS────────────────────────────────────
    sc_in <sc_uint<32>>  address;                                                               // address input 
    sc_out<sc_bv  <32>>  instruction;                                                           // instruction output

    // ───────────────────────────DECLARATION MEMORY────────────────────────────────
    std::vector<sc_bv<32>> mem;                                                                         

    std::size_t size() const { return mem.size(); }                                             // returning size of instruction memory (How many instructions in many)


    void load_memory(const std::string& filePath = "files/instructions.bin")
    {
        std::ifstream f(filePath);                                                              // handling file not exist error
        if (!f.is_open()) {
            SC_REPORT_ERROR("/IMEM", ("cannot open " + filePath).c_str());
            return;
        }

        std::string line;
        // ───────────────────────────TRIMMING WHITE SPACES IN INSTRUCTION FILE────────────────────────────────
        while (std::getline(f, line))
        {

            const auto first = line.find_first_not_of(" \t\r\n");                               // scan from the beginning of line if there is any white spaces
            const auto last  = line.find_last_not_of (" \t\r\n");                               // scan from the end of line if there is any white spaces
            if (first == std::string::npos) continue;                                           // blank line like this "        ",,, npos--> no position
            line = line.substr(first, last - first + 1);                                        // Fetching the real content in line(instruction) without any white spaces                                        

            if (line.length() != 32) {                                                          // check if the string length is 32 bit to be a valid instruction based on its ISA
                SC_REPORT_WARNING("/IMEM",
                    ("ignored line with length " + std::to_string(line.length()))
                    .c_str());
                continue;
            }
            mem.emplace_back(line.c_str());                                                     // create a new element directly inside the vector
        }
        f.close();
    }

    void read_from_rom()                                                                     
    {
        const auto a = address.read();                                                          // address cannot be changed after it assigned
        if (a < mem.size())
            instruction.write(mem[a]);                                                          // fetching instruction from memory if address in range
        else                       
            instruction.write(sc_bv<32>(0));                                                    // if address out of range writing 0 on output
    }

    SC_CTOR(Instruction_Memory)
    {
        load_memory();                                                                          // initialiaing and filling instructions in memory before fetching before time 0 (first instruction)
        SC_METHOD(read_from_rom);                                                               // read from ROM combinationally
        sensitive << address;                                                                   // function calling sensitive to adddress changing
    }
};
#endif
