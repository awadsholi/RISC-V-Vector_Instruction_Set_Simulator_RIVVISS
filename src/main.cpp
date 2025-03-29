#include "register_types.h"
#include "functions.h"
#include "instructions.h"
#include "modules/fetch_to_execution.h"

Register_Status* reg_status = nullptr;
sc_bv<32>* memory = nullptr;
int INSTRUCTION_MEMORY_SIZE;

int sc_main(int argc, char* argv[]) {

    reg_status = new Register_Status();
    readConfigurationFile("files/cofigure.txt");
    ReadConfigurationFileParameters();

    memory = new sc_bv<32>[INSTRUCTION_MEMORY_SIZE];
    for (int i = 0; i < INSTRUCTION_MEMORY_SIZE ; ++i) {
        memory[i] = sc_bv<32>();  
    }

    reg_status->Vector_Register[1].range(31,0) = sc_bv<32>(9);
    reg_status->Vector_Register[1].range(63,32) = sc_bv<32>(15);
    reg_status->Vector_Register[1].range(95,64) = sc_bv<32>(-134);
    reg_status->Vector_Register[1].range(127,96) = sc_bv<32>(13);
    reg_status->Vector_Register[1].range(159,128) = sc_bv<32>(141);
    reg_status->Vector_Register[1].range(191,160) = sc_bv<32>(41);
    reg_status->Vector_Register[1].range(223,192) = sc_bv<32>(-31);
    reg_status->Vector_Register[1].range(255,224) = sc_bv<32>(-141);

    reg_status->Vector_Register[2].range(31,0)  = sc_bv<32>(12);
    reg_status->Vector_Register[2].range(63,32) = sc_bv<32>(21);
    reg_status->Vector_Register[2].range(95,64) = sc_bv<32>(15);
    reg_status->Vector_Register[2].range(127,96) = sc_bv<32>(-1);
    reg_status->Vector_Register[2].range(159,128) = sc_bv<32>(31);
    reg_status->Vector_Register[2].range(191,160) = sc_bv<32>(12);
    reg_status->Vector_Register[2].range(223,192) = sc_bv<32>(142);
    reg_status->Vector_Register[2].range(255,224) = sc_bv<32>(25);

  
    // Create signal and module BEFORE starting simulation
    Fetch_To_Execution fetcth_to_execution("fetch_execution");

    sc_start();  // Start simulation AFTER setup

    printRegisterStatus(reg_status);

    free_resourses(reg_status);

    return 0;
}