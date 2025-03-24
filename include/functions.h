#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include "include/register_types.h"

std::string decimalToBinary(int num);
void printRegisterStatus(Register_Status* reg_status);
void free_resourses(Register_Status* reg_status);
void readConfigurationFile(const std::string& filePath);
void ReadConfigurationFileParameters();

#endif