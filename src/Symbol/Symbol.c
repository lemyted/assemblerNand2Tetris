#include "Symbol.h"

struct HackSymbol symbols[] = {
  {"SP", SP},
  {"LCL", LCL},
  {"ARG", ARG},
  {"THIS", THIS},
  {"THAT", THAT},
  {"R0", R0},
  {"R1", R1},
  {"R2", R2},
  {"R3", R3},
  {"R4", R4},
  {"R5", R5},
  {"R6", R6},
  {"R7", R7},
  {"R8", R8},
  {"R9", R9},
  {"R10", R10},
  {"R11", R11},
  {"R12", R12},
  {"R13", R13},
  {"R14", R14},
  {"R15", R15}
};

int getLengthSymbols()
{
  return sizeof symbols / sizeof (struct HackSymbol);
}

int getRAMAddressSymbol(char *label) 
{
  int len = getLengthSymbols();

  for (int i = 0; i < len; i++)
  {
    bool isAMatch = strcmp(symbols[i].label, label) == 0;
     
    if (isAMatch) 
    {
      return symbols[i].address;
    }
  }
  
  return -1;
}

