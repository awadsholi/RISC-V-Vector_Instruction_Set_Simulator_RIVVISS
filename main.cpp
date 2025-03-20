#include <iostream>
#include <fstream>
#include <string>
#include <cstdio> 
#include <stdlib.h>
#include <string.h>
#include <systemc.h>
#define NUMBER_OF_REGISTERS 32

typedef struct {
    int SEW;
    float LMUL;
    char TA;
    char MA;
} Vtype;


typedef struct{
    char *Register0;
    int * Register [NUMBER_OF_REGISTERS-1];
    int VLEN;
    int AVL;
    int VL; 
    int VLMAX;    
    Vtype vtype;
}Register_Status;
sc_bv<32>* memory = nullptr;

int Number_of_instructions = 0;
Register_Status *reg_status = nullptr;
std::string binary_conf = "";
int INSTRUCTION_MEMORY_SIZE;

         //      Functions prototypes     //

void free_resourses(Register_Status *reg_status);              
void printRegisterStatus(Register_Status *reg_status);
std::string decimalToBinary(int num) ;
void readConfigurationFile(const std::string& filePath);
void ReadConfigurationFileParameters();



////    INSTRUCTIONS FUNCTIONS  ////

void vadd_vv(Register_Status * register_status, uint8_t vd, uint8_t vs1, uint8_t vs2) {     //VADD_VV
    for (uint64_t i = 0; i < register_status->VL; i++) {
        register_status->Register[vd - 1][i] = 
        register_status->Register[vs1 - 1][i] + register_status->Register[vs2 - 1][i];
    }
}

void vsub_vv(Register_Status * register_status, uint8_t vd, uint8_t vs1, uint8_t vs2) {      //VSUB_VV
    for (uint64_t i = 0; i < register_status->VL; i++) {
        register_status->Register[vd - 1][i] = 
        register_status->Register[vs2 - 1][i] - register_status->Register[vs1 - 1][i];
    }
}


void free_resourses(Register_Status *reg_status){

    for(int i=0;i<NUMBER_OF_REGISTERS-1;i++){
        free(reg_status->Register[i]);
    }
    free(reg_status->Register0);
    delete [] memory;
}


void printRegisterStatus(Register_Status *reg_status) {

    if (reg_status == NULL) {
        printf("Register_Status is NULL.\n");
        return;
    }
  
    printf("Register_Status Information:\n");
    printf("VLEN  : %d\n", reg_status->VLEN);
    printf("AVL   : %d\n", reg_status->AVL);
    printf("VL    : %d\n", reg_status->VL);
    printf("VLMAX : %d\n", reg_status->VLMAX);

    printf("\nVtype Information:\n");
    printf("SEW   : %d\n", reg_status->vtype.SEW);
    printf("LMUL  : %.2f\n", reg_status->vtype.LMUL);
    printf("TA    : %c\n", reg_status->vtype.TA);
    printf("MA    : %c\n", reg_status->vtype.MA);

    printf("\nRegister Addresses:\n");

    printf("Register[0]: ");
    for (int i = 0; i < reg_status->VLEN; i++){
        printf("%d, ", reg_status->Register0[i]);
    }
    printf("\n");

    for (int i = 0; i < NUMBER_OF_REGISTERS-1; i++) {
            
            printf("Register[%d]: ",i+1);
            for (int j = 0; j < reg_status->VLMAX; j++)
            {
                printf("%d, ", reg_status->Register[i][j]);
            }
            printf("\n"); 
    }    
}



std::string decimalToBinary(int num) {
    num &= 0x3FF;  // Ensure the binary Size is 10-bit 
    std::string binary;
    
    
    for (int i = 0; i < 10; ++i) { 
        if(num%2 == 0){
            binary = "0" + binary;
        }
        else{
            binary = "1" + binary;
        }

        num /= 2;
    }
    
    return binary;
}



void readConfigurationFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
                                /*FILE LOST STATUS*/
        binary_conf = "0000000010";
        reg_status->AVL = 8;
        reg_status->VLEN = 256;
        return;
    }

    std::string line;
    char key[35];
    int value;

    while (std::getline(file, line)) {
        if (std::sscanf(line.c_str(), "%s %d", key, &value) == 2) {
            if (std::string(key) == "VTYPE") {
                std::cout << "vtype: " << value << std::endl;
                binary_conf = decimalToBinary(value);
                std::cout << "Binary: " << binary_conf << std::endl;
            }

            else if (std::string(key) == "VLEN") {
                std::cout << "vlen: " << value << std::endl;
                reg_status->VLEN = value;
            }

            else if (std::string(key) == "AVL") {
                std::cout << "AVL: " << value << std::endl;
                reg_status->AVL = value;
            }
            else if (std::string(key) == "INSTRUCTION_MEMORY_SIZE") {
                std::cout << "INSTRUCTION_MEMORY_SIZE: " << value << std::endl;
                INSTRUCTION_MEMORY_SIZE = value;
            }
        }
    }
}


void ReadConfigurationFileParameters(){
    reg_status->vtype = {0};
    char SEW[4] = {'\0'};  
    char LMUL[4] = {'\0'};

    for (int i = 0; i < binary_conf.length(); i++) {
        if(i==0){
            reg_status->vtype.MA = binary_conf[i];
            
        }
        else if(i==1){
            reg_status->vtype.TA = binary_conf[i];
        }
        else if(i>3 && i<= 6){
            LMUL[i - 4] = binary_conf[i];
        }
        else if(i>6 && i<=9){
            SEW[i - 7] = binary_conf[i];
        }
    }

    int sewValue = 0;
    if (SEW[0] == '1') 
        sewValue += 4;

    if (SEW[1] == '1') 
        sewValue += 2;

    if (SEW[2] == '1') 
        sewValue += 1;

    switch (sewValue) {
        case 0: 
            reg_status->vtype.SEW = 8; 
            break;
        case 1:
            reg_status->vtype.SEW = 16; 
            break;
        case 2:  
        default: 
            reg_status->vtype.SEW = 32; 
            break;
    }

    int lmulValue = 0;
    if (LMUL[0] == '1')
        lmulValue += 4;

    if (LMUL[1] == '1') 
        lmulValue += 2;

    if (LMUL[2] == '1') 
        lmulValue += 1;

    switch (lmulValue) {
        case 0:  
            reg_status->vtype.LMUL = 1.0f;
            break;
        case 1:
            reg_status->vtype.LMUL = 2.0f; 
            break;
        case 2: 
            reg_status->vtype.LMUL = 4.0f; 
            break;
        case 3:
            reg_status->vtype.LMUL = 8.0f;
            break;
        case 7:
            reg_status->vtype.LMUL = 0.5f; 
            break;  
        default: 
            reg_status->vtype.LMUL = 1.0f;
            break;
    }
    reg_status->VLMAX = (reg_status->VLEN/reg_status->vtype.SEW) * reg_status->vtype.LMUL;  //calculating VLMAX(number of elements)

    for (int i = 0; i < NUMBER_OF_REGISTERS-1; i++)
    {
        reg_status->Register[i] =(int *) malloc(sizeof(int) * reg_status->VLMAX);         //allocate enough space for V1-V31 and set the values to zero
          if (reg_status->Register[i] !=nullptr)
            {         
            memset(reg_status->Register[i], 0 , sizeof(int) * reg_status->VLMAX);
            }    

    }

    reg_status->Register0 = (char *)malloc(reg_status->VLEN);           //allocate enough space for V0 and set the values to zero
    memset(reg_status->Register0, 0 , reg_status->VLEN);
    reg_status->VL = (reg_status->AVL > reg_status->VLMAX) ? reg_status->VLMAX: reg_status->AVL;

}

///////////             DECODE AND EXECUTION STAGE          ///////////////
SC_MODULE(Decode_Execution_Stage) {
    sc_in<sc_bv<32>> instruction;

    SC_CTOR(Decode_Execution_Stage) {
        SC_METHOD(decode_process);
        sensitive << instruction;  // Trigger on instruction changes
    }

    void decode_process() {
        sc_bv<32> instr = instruction.read();
        std:: cout << "Instrution: " << instr << endl;
    }
};

/////               INSTRUCTION MEMORY MODULE           //////////

SC_MODULE(Instruction_Memory) {
    sc_in<sc_uint<8>> address;
    sc_out<sc_bv<32>> instruction;
    sc_bv<32> instruction_div;    /// for takes the value of instrution to split 

    sc_bv<6> funct6;
    sc_bv<1> vm;
    unsigned int vs2;
    unsigned int vs1;
    sc_bv<3> funct3;
    unsigned int vd;
    sc_bv<7> opcode;

    const std::string filePath = "instructions.bin";

    void read_from_rom() {
        instruction.write(memory[address.read()]);
        //Decode
        ///division of the instruction
        instruction_div = memory[address.read()];
        funct6 = instruction_div.range(31,26);
        vm = instruction_div.range(25,25);
        vs2 = instruction_div.range(24,20).to_uint();
        vs1 = instruction_div.range(19,15).to_uint();
        funct3 = instruction_div.range(14,12);
        vd = instruction_div.range(11,7).to_uint();
        opcode = instruction_div.range(6,0);
         
        switch(opcode.to_uint()){
            case 0b1010111: 
                switch (funct6.to_uint())
                {   
                    case 0b000000:                  // Vadd
                        switch (funct3.to_uint()) 
                        {
                            case 0b000:             // Vector to Vector
                                if(vm.to_uint()){   // Masking disabled
                                    vadd_vv(reg_status,vd,vs1,vs2);
                                } else{             // Masking Enabled
                                                    
                                }

                            break;
                        }
                    break;

                    case 0b000010:
                        switch (funct3.to_uint()) 
                        {
                            case 0b000:             // Vector to Vector
                                if(vm.to_uint()){   // Masking disabled
                                    vsub_vv(reg_status,vd,vs1,vd);
                                } else{             // Masking Enabled
                                                    
                                }

                            break;
                        }
                    break;
                }
            break;
        }
    
        
        // std::cout << "OPCODE: " << opcode << endl;
        // std::cout << "funct6: " << funct6 << endl;
        // std::cout << "vs1: " << vs1 << endl;
        // std::cout << "vs2: " << vs2 << endl;
        // std::cout << "vd: " << vd << endl;
        
        printf("\n\n\n\n\n\n\n\n");
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
        while (std::getline(file, line) && i < INSTRUCTION_MEMORY_SIZE / 4) {
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

///                 FETCH STAGE         ////////////////


SC_MODULE(Instruction_Fetch_Stage) {
    sc_out<sc_bv<32>> instruction_out;
    Instruction_Memory instruction_memory_instance;
    // Decode_Execution_Stage decode_execution_stage;
    sc_signal<sc_uint<8>> PC;

    SC_CTOR(Instruction_Fetch_Stage) 
      : instruction_memory_instance("im")
    {
        instruction_memory_instance.address(PC);
        instruction_memory_instance.instruction(instruction_out);
        // decode_execution_stage.instruction(instruction_out);
        PC.write(0);
        SC_THREAD(fetch);
    }

    void fetch() {
        wait(SC_ZERO_TIME);  // Let initial instruction propagate

        while(true) {
            sc_uint<8> current_pc = PC.read();
            
            

            // Check exit condition
            if(current_pc == (INSTRUCTION_MEMORY_SIZE/4) - 1) {
                sc_stop();
                break;
            }

            // Increment PC and wait
            PC.write(current_pc + 1);
            wait(1, SC_NS);
        }
    }

    void reset_pc() { PC.write(0); }
};






int sc_main(int argc, char* argv[]) {
    reg_status = new Register_Status;
    readConfigurationFile("cofigure.txt");
    ReadConfigurationFileParameters();
    memory = new sc_bv<32>[INSTRUCTION_MEMORY_SIZE / 4];
    for (int i = 0; i < INSTRUCTION_MEMORY_SIZE / 4; ++i) {
        memory[i] = sc_bv<32>();  
    }
    
    reg_status->Register[1][0] = 4;
    reg_status->Register[1][1] = 5;
    reg_status->Register[1][2] = 6;
    reg_status->Register[1][3] = 7;


    reg_status->Register[2][0] = 3;
    reg_status->Register[2][1] = 2;

        
    reg_status->Register[2][2] = 1;
    reg_status->Register[2][3] = 1;
  
    // Create signal and module BEFORE starting simulation
    sc_signal<sc_bv<32>> instruction_signal;
    Instruction_Fetch_Stage IF("IF");
    IF.instruction_out(instruction_signal);  // Bind port

    sc_start();  // Start simulation AFTER setup

    printRegisterStatus(reg_status);

    free_resourses(reg_status);

    return 0;
}




