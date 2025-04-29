#include "register_types.h"
#include "functions.h"
#include "instructions.h"
#include "modules/fetch_to_execution.h"
#include "modules/datamemory.h"

Register_Status* reg_status = nullptr;
Memory* datamem = nullptr;
int sc_main(int argc, char* argv[]) {
    Memory* datamem = new Memory();
    reg_status = new Register_Status();

    readConfigurationFile("files/cofigure.txt");
    ReadConfigurationFileParameters();

    sc_signal<sc_bv<32>> fetched_instr;
    Instruction_Fetch_Stage if_stage("IF");
    if_stage.instruction_out(fetched_instr);

    reg_status->Vector_Register[0].range(7, 0)   = sc_bv<8>(1);
    reg_status->Vector_Register[0].range(15, 8)  = sc_bv<8>(1);   
    reg_status->Vector_Register[0].range(23, 16) = sc_bv<8>(1);
    reg_status->Vector_Register[0].range(31, 24) = sc_bv<8>(1);

    reg_status->Vector_Register[1].range(7, 0)   = sc_bv<8>(10);     
    reg_status->Vector_Register[1].range(15, 8)  = sc_bv<8>(127);     
    reg_status->Vector_Register[1].range(23, 16) = sc_bv<8>(80);    
    reg_status->Vector_Register[1].range(31, 24) = sc_bv<8>(-78);    
    reg_status->Vector_Register[1].range(39, 32) = sc_bv<8>(0);    
    reg_status->Vector_Register[1].range(47, 40) = sc_bv<8>(2);    
    reg_status->Vector_Register[1].range(55, 48) = sc_bv<8>(14);    
    reg_status->Vector_Register[1].range(63, 56) = sc_bv<8>(2);
    
    reg_status->Vector_Register[2].range(7, 0)   = sc_bv<8>(1);    
    reg_status->Vector_Register[2].range(15, 8)  = sc_bv<8>(-1);    
    reg_status->Vector_Register[2].range(23, 16) = sc_bv<8>(-3);    
    reg_status->Vector_Register[2].range(31, 24) = sc_bv<8>(4);    
    reg_status->Vector_Register[2].range(39, 32) = sc_bv<8>(3);    
    reg_status->Vector_Register[2].range(47, 40) = sc_bv<8>(-34);
    reg_status->Vector_Register[2].range(55, 48) = sc_bv<8>(22);
    reg_status->Vector_Register[2].range(63, 56) = sc_bv<8>(0);      
    
    // reg_status->Vector_Register[1].range(15, 0)   = sc_bv<16>(32767);     
    // reg_status->Vector_Register[1].range(31, 16)  = sc_bv<16>(-32768);  
    // reg_status->Vector_Register[1].range(47, 32)  = sc_bv<16>(16384); 
    // reg_status->Vector_Register[1].range(63, 48)  = sc_bv<16>(-16384);   
    // reg_status->Vector_Register[1].range(79, 64)  = sc_bv<16>(0);  
    // reg_status->Vector_Register[1].range(95, 80)  = sc_bv<16>(32767);   
    // reg_status->Vector_Register[1].range(111, 96) = sc_bv<16>(-32768);  
    // reg_status->Vector_Register[1].range(127, 112)= sc_bv<16>(20000); 

    // reg_status->Vector_Register[2].range(15, 0)   = sc_bv<16>(32767);     
    // reg_status->Vector_Register[2].range(31, 16)  = sc_bv<16>(-32767);    
    // reg_status->Vector_Register[2].range(47, 32)  = sc_bv<16>(16384);    
    // reg_status->Vector_Register[2].range(63, 48)  = sc_bv<16>(-16384);    
    // reg_status->Vector_Register[2].range(79, 64)  = sc_bv<16>(0);    
    // reg_status->Vector_Register[2].range(95, 80)  = sc_bv<16>(-1);    
    // reg_status->Vector_Register[2].range(111, 96) = sc_bv<16>(32767);   
    // reg_status->Vector_Register[2].range(127, 112)= sc_bv<16>(20000);   
   

    // reg_status->Vector_Register[1].range(31,0) = sc_bv<32>(65535);
    // reg_status->Vector_Register[1].range(63,32) = sc_bv<32>(65536);
    // reg_status->Vector_Register[1].range(95,64) = sc_bv<32>(65539);
    // reg_status->Vector_Register[1].range(127,96) = sc_bv<32>(65540);
    // reg_status->Vector_Register[1].range(159,128) = sc_bv<32>(1);
    // reg_status->Vector_Register[1].range(191,160) = sc_bv<32>(2);
    // reg_status->Vector_Register[1].range(223,192) = sc_bv<32>(4);
    // reg_status->Vector_Register[1].range(255,224) = sc_bv<32>(65538);

    // reg_status->Vector_Register[2].range(31,0)  = sc_bv<32>(21474);
    // reg_status->Vector_Register[2].range(63,32) = sc_bv<32>(83648);
    // reg_status->Vector_Register[2].range(95,64) = sc_bv<32>(24);
    // reg_status->Vector_Register[2].range(127,96) = sc_bv<32>(4);
    // reg_status->Vector_Register[2].range(159,128) = sc_bv<32>(10);
    // reg_status->Vector_Register[2].range(191,160) = sc_bv<32>(31);
    // reg_status->Vector_Register[2].range(223,192) = sc_bv<32>(837);
    // reg_status->Vector_Register[2].range(255,224) = sc_bv<32>(343);
  

    // reg_status->Vector_Register[2].range(63, 0)    = sc_bv<64>(static_cast<long long>(9223372036854775807LL));   
    // reg_status->Vector_Register[2].range(127, 64)  = sc_bv<64>(20);  
    // reg_status->Vector_Register[2].range(191, 128) = sc_bv<64>(25);   
    // reg_status->Vector_Register[2].range(255, 192) = sc_bv<64>(6);  
    // reg_status->Vector_Register[2].range(319, 256) = sc_bv<64>(7);   
    // reg_status->Vector_Register[2].range(383, 320) = sc_bv<64>(67);   
    // reg_status->Vector_Register[2].range(447, 384) = sc_bv<64>(78);   
    // reg_status->Vector_Register[2].range(511, 448) = sc_bv<64>(static_cast<long long>(-9223372036854775807LL - 1));   
  
    // Create signal and module BEFORE starting simulation
    Fetch_To_Execution fetcth_to_execution("fetch_execution");

    sc_start();  // Start simulation AFTER setup

    printRegisterStatus(reg_status);

    free_resourses(reg_status);

    return 0;
}