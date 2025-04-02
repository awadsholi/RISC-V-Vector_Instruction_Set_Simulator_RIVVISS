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

    // reg_status->Vector_Register[1].range(15, 0)   = sc_bv<16>(9);     // First 16-bit element
    // reg_status->Vector_Register[1].range(31, 16)  = sc_bv<16>(15);    // Second 16-bit element
    // reg_status->Vector_Register[1].range(47, 32)  = sc_bv<16>(-134);  // Third element
    // reg_status->Vector_Register[1].range(63, 48)  = sc_bv<16>(13);    // Fourth element
    // reg_status->Vector_Register[1].range(79, 64)  = sc_bv<16>(141);   // Fifth element
    // reg_status->Vector_Register[1].range(95, 80)  = sc_bv<16>(41);    // Sixth element
    // reg_status->Vector_Register[1].range(111, 96) = sc_bv<16>(-31);   // Seventh element
    // reg_status->Vector_Register[1].range(127, 112)= sc_bv<16>(-141);  // Eighth element

    // reg_status->Vector_Register[2].range(15, 0)   = sc_bv<16>(1);     
    // reg_status->Vector_Register[2].range(31, 16)  = sc_bv<16>(2);    
    // reg_status->Vector_Register[2].range(47, 32)  = sc_bv<16>(4);    
    // reg_status->Vector_Register[2].range(63, 48)  = sc_bv<16>(0);    
    // reg_status->Vector_Register[2].range(79, 64)  = sc_bv<16>(7);    
    // reg_status->Vector_Register[2].range(95, 80)  = sc_bv<16>(0);    
    // reg_status->Vector_Register[2].range(111, 96) = sc_bv<16>(8);   
    // reg_status->Vector_Register[2].range(127, 112)= sc_bv<16>(-1);   

    // reg_status->Vector_Register[1].range(7, 0)   = sc_bv<8>(0x09);     
    // reg_status->Vector_Register[1].range(15, 8)  = sc_bv<8>(0x03);     
    // reg_status->Vector_Register[1].range(23, 16) = sc_bv<8>(0x07);    
    // reg_status->Vector_Register[1].range(31, 24) = sc_bv<8>(0x01);    
    // reg_status->Vector_Register[1].range(39, 32) = sc_bv<8>(0x0F);    
    // reg_status->Vector_Register[1].range(47, 40) = sc_bv<8>(0x05);    
    // reg_status->Vector_Register[1].range(55, 48) = sc_bv<8>(0xAB);    
    // reg_status->Vector_Register[1].range(63, 56) = sc_bv<8>(0x0C);     

    // reg_status->Vector_Register[2].range(7, 0)   = sc_bv<8>(1);    
    // reg_status->Vector_Register[2].range(15, 8)  = sc_bv<8>(0);    
    // reg_status->Vector_Register[2].range(23, 16) = sc_bv<8>(7);    
    // reg_status->Vector_Register[2].range(31, 24) = sc_bv<8>(0);    
    // reg_status->Vector_Register[2].range(39, 32) = sc_bv<8>(3);    
    // reg_status->Vector_Register[2].range(47, 40) = sc_bv<8>(0);    
    // reg_status->Vector_Register[2].range(55, 48) = sc_bv<8>(4);    
    // reg_status->Vector_Register[2].range(63, 56) = sc_bv<8>(0);    

    reg_status->Vector_Register[1].range(31,0) = sc_bv<32>(9);
    reg_status->Vector_Register[1].range(63,32) = sc_bv<32>(15);
    reg_status->Vector_Register[1].range(95,64) = sc_bv<32>(-134);
    reg_status->Vector_Register[1].range(127,96) = sc_bv<32>(13);
    reg_status->Vector_Register[1].range(159,128) = sc_bv<32>(141);
    reg_status->Vector_Register[1].range(191,160) = sc_bv<32>(41);
    reg_status->Vector_Register[1].range(223,192) = sc_bv<32>(-31);
    reg_status->Vector_Register[1].range(255,224) = sc_bv<32>(-141);

    reg_status->Vector_Register[2].range(31,0)  = sc_bv<32>(327683);
    reg_status->Vector_Register[2].range(63,32) = sc_bv<32>(4);
    reg_status->Vector_Register[2].range(95,64) = sc_bv<32>(7);
    reg_status->Vector_Register[2].range(127,96) = sc_bv<32>(-1);
    reg_status->Vector_Register[2].range(159,128) = sc_bv<32>(8);
    reg_status->Vector_Register[2].range(191,160) = sc_bv<32>(-56);
    reg_status->Vector_Register[2].range(223,192) = sc_bv<32>(1);
    reg_status->Vector_Register[2].range(255,224) = sc_bv<32>(2);

  
    // Create signal and module BEFORE starting simulation
    Fetch_To_Execution fetcth_to_execution("fetch_execution");

    sc_start();  // Start simulation AFTER setup

    printRegisterStatus(reg_status);

    free_resourses(reg_status);

    return 0;
}