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

Register_Status *reg_status = nullptr;
std::string binary_conf = "";


         //      Functions prototypes     //

void free_resourses(Register_Status *reg_status);              
void printRegisterStatus(Register_Status *reg_status);
std::string decimalToBinary(int num) ;
void readConfigurationFile(const std::string& filePath);
void ReadConfigurationFileParameters();





void free_resourses(Register_Status *reg_status){

    for(int i=0;i<NUMBER_OF_REGISTERS-1;i++){
        free(reg_status->Register[i]);
    }
    free(reg_status->Register0);

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
    char key[10];
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




SC_MODULE(Instruction_Memory) {
    sc_in<sc_uint<8>> address;
    sc_out<sc_bv<32>> instruction;

    sc_bv<32> memory[256];  // 256 x 32-bit memory

    const std::string filePath = "instructions.bin";

    void read_from_rom() {
        instruction.write(memory[address.read()]);
        //Decode
        std::cout << "Instruction :" << instruction<<endl;
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






int sc_main(int argc, char* argv[]) {
    reg_status = new Register_Status;
    readConfigurationFile("cofigure.txt");
    ReadConfigurationFileParameters();

    // Create signal and module BEFORE starting simulation
    sc_signal<sc_bv<32>> instruction_signal;
    Instruction_Fetch_Stage IF("IF");
    IF.instruction_out(instruction_signal);  // Bind port

    sc_start();  // Start simulation AFTER setup

   

    free_resourses(reg_status);
    return 0;
}