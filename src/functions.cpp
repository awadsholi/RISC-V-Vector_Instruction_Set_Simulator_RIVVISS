#include "functions.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

std::string binary_conf = "";

std::string decimalToBinary(int num) {
    num &= 0x3FF;                    // Ensure the binary Size is 10-bit 
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

void printRegisterStatus(Register_Status *reg_status) {

    if (reg_status == NULL) {
        printf("Register_Status is NULL.\n");
        return;
    }
  
    printf("Register_Status Information:\n");
    printf("VL    : %d\n", reg_status->VL);
    printf("VLMAX : %d\n", reg_status->VLMAX);

    printf("\nVtype Information:\n");
    printf("SEW   : %d\n", reg_status->vtype.SEW);
    printf("LMUL  : %.2f\n", reg_status->vtype.LMUL);
    printf("TA    : %c\n", reg_status->vtype.TA);
    printf("MA    : %c\n", reg_status->vtype.MA);

    printf("\n\n");

    for (int i = 0; i < NUMBER_OF_REGISTERS; i++) {
            printf("Vector_Register[%d]: ",i);

            for (int j = 0; j < VLEN ; j=j+reg_status->vtype.SEW){

                int64_t val = reg_status->Vector_Register[i].range(j + reg_status->vtype.SEW - 1, j).to_int64();  // sign-extended to 64 bits internally
                switch (reg_status->vtype.SEW) {
                    case 8:  printf("%d, ",  static_cast<int8_t>(val));  break;     //signed 8 bit 
                    // case 8:  printf("%u, ",  static_cast<uint8_t>(val));  break;       //unsigned 8 bit 
                    case 16: printf("%d, ",  static_cast<int16_t>(val)); break;        //signed 16 bit
                    // case 16: printf("%u, ",  static_cast<uint16_t>(val)); break;       //unsigned 16 bit 
                    case 32: printf("%d, ",  static_cast<int32_t>(val)); break;        //signed 32 bit 
                    // case 32: printf("%u, ",  static_cast<uint32_t>(val)); break;       //unsigned 32 bit 
                    case 64: printf("%lld, ", static_cast<long long>(val)); break;      //signed 64 bit
                    // case 64: printf("%llu, ", static_cast<unsigned long long>(val)); break;      //unsigned 64 bit
                }

            }
            printf("\n"); 
    }    
}

void free_resourses(Register_Status *reg_status){                         //Realese resourses 

    free(reg_status);
    delete [] memory;

}


void readConfigurationFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
                                /*FILE LOST STATUS*/
        binary_conf = "0000000010";
        reg_status->AVL = 8;
        return;
    }

    std::string line;
    char key[35];
    int value;

    while (std::getline(file, line)) {
        if (std::sscanf(line.c_str(), "%s %d", key, &value) == 2) {
            if (std::string(key) == "VTYPE") {
                binary_conf = decimalToBinary(value);
            }

            else if (std::string(key) == "AVL") {
                reg_status->AVL = value;
            }
            else if (std::string(key) == "INSTRUCTION_MEMORY_SIZE") {
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
            reg_status->vtype.SEW = 32; 
            break;
        case 3:     
            reg_status->vtype.SEW = 64; 
            break;
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

    reg_status->VLMAX = (VLEN/reg_status->vtype.SEW) * reg_status->vtype.LMUL;  //calculating VLMAX(number of elements)

    reg_status->VL = (reg_status->AVL > reg_status->VLMAX) ? reg_status->VLMAX: reg_status->AVL;

}