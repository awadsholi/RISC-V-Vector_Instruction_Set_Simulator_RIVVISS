#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include "register_types.h"

std::string decimalToBinary(int num);
void printRegisterStatus(Register_Status* reg_status);
void free_resourses(Register_Status*& reg_status);
void readConfigurationFile(const std::string& filePath);
void ReadConfigurationFileParameters();
sc_bv<128> RoundOff(sc_bv<128> V,uint64_t Shift_amount , uint8_t Rounding_Mode , uint8_t Signed_flag);

#endif