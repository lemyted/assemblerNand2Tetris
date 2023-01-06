#include <CUnit/CUnit.h>
#include <CUnit/Console.h>
#include <CUnit/Basic.h>
#include "../../Symbol/Symbol.h"
#include "Parser.h"

FILE *openFile(char* name, char *mode);

bool hasComment(char *line);

void ltrim(char *str);

void rtrim(char *str);

void trim(char *str);

void filterComment(char *line);

void convertToBase2_16Bit(int val, char *res);

int isRegA(char *instr);

char *handleRegAInstruction(char *str);

char *asmToBin(char *line);

void translate(FILE *inputFile, FILE *outputFile);