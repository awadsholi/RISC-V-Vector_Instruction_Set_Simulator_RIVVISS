#include "include/register_types.h"
#include "include/functions.h"
#include "include/instructions.h"
#include "include/modules/fetch_to_execution.h"

Register_Status* reg_status = nullptr;
sc_bv<32>* memory = nullptr;
int INSTRUCTION_MEMORY_SIZE;


int sc_main(int argc, char* argv[]) {

    reg_status = new Register_Status;
    readConfigurationFile("files/cofigure.txt");
    ReadConfigurationFileParameters();

    memory = new sc_bv<32>[INSTRUCTION_MEMORY_SIZE];
    for (int i = 0; i < INSTRUCTION_MEMORY_SIZE ; ++i) {
        memory[i] = sc_bv<32>();  
    }

    reg_status->Vector_Register[0][0] = 9;
    reg_status->Vector_Register[0][1] = 15;
    reg_status->Vector_Register[0][2] = -134;
    reg_status->Vector_Register[0][3] = 13;
    reg_status->Vector_Register[0][4] = 141;
    reg_status->Vector_Register[0][5] = 41;
    reg_status->Vector_Register[0][6] = -31;
    reg_status->Vector_Register[0][7] = -141;

    reg_status->Vector_Register[1][0] = -12;
    reg_status->Vector_Register[1][1] = 21;
    reg_status->Vector_Register[1][2] = 15;
    reg_status->Vector_Register[1][3] = 31;
    reg_status->Vector_Register[1][4] = 31;
    reg_status->Vector_Register[1][5] = 12;
    reg_status->Vector_Register[1][6] = 142;
    reg_status->Vector_Register[1][7] = 25;
  
    // Create signal and module BEFORE starting simulation
    Fetch_To_Execution fetcth_to_execution("fetch_execution");

    sc_start();  // Start simulation AFTER setup

    printRegisterStatus(reg_status);

    free_resourses(reg_status);

    return 0;
}