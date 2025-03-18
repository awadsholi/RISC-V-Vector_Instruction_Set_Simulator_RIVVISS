#include <iostream>
#include <fstream>
#include <string>
#include <cstdio> 
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_REGISTERS 32

typedef struct {
    int SEW;
    float LMUL;
    char TA;
    char MA;
} Vtype;





typedef struct{
    int * Register [NUMBER_OF_REGISTERS];
    int VLEN;
    int AVL;
    int VL; 
    int VLMAX;    
    Vtype vtype;
}Register_Status;

Register_Status *reg_status = nullptr;


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
    for (int i = 0; i < NUMBER_OF_REGISTERS; i++) {
        printf("Register[%d]: ",i);
        if (i==0) { 
            for (int j = 0; j < reg_status->VLEN; j++)
            {
                printf("%d, ",  reg_status->Register[i][j]);
            }
            printf("\n");
        }
       
        
        else{
            for (int j = 0; j < reg_status->VLMAX; j++)
            {
                printf("%d, ", reg_status->Register[i][j]);
            }
            printf("\n");
        }
        
       
    }
}

std::string binary_conf = "";


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
    reg_status->VLMAX = (reg_status->VLEN/reg_status->vtype.SEW) * reg_status->vtype.LMUL;

    for (int i = 0; i < NUMBER_OF_REGISTERS; i++)
    {
        if(i == 0){
            reg_status->Register[i] = ( int* )malloc(sizeof( int) * reg_status->VLEN);
            memset(reg_status->Register[i], 0 , sizeof(int) * reg_status->VLEN);
        }
            else{
            reg_status->Register[i] = ( int* )malloc(sizeof(int) * reg_status->VLMAX);
        
            if (reg_status->Register[i] !=nullptr)
            {         
                memset(reg_status->Register[i], 0 , sizeof(int) * reg_status->VLMAX);
            }

        }
    }
    reg_status->VL = (reg_status->AVL > reg_status->VLMAX) ? reg_status->VLMAX: reg_status->AVL;
    printRegisterStatus(reg_status);

}

int main() {
   
    reg_status = new Register_Status;
    readConfigurationFile("cof.txt");
    ReadConfigurationFileParameters();
    return 0;
}