#include "Parser.h"
#include "../Symbol/Symbol.h"

#define COMMENT "//"

int paramsOk(int argc, char* argv[]) 
{
  if (argc < 3) 
  {
    printf("paramsOk: Expected 3 arguments\n");
    return false;
  }

  if (strstr(argv[1], ".asm\0") == NULL || strstr(argv[2], ".hack\0") == NULL)
  {
    printf("paramsOk: Expected arguments [bin] [input].asm [output].hack\n");
    return 0;
  }
  return 1;
}

FILE *openFile(char* name, char *mode) 
{
  FILE *fptr;
  char ext[] = ".hack";

  if (strcmp("w", mode) && strstr(name, ext)) 
  {
    printf("openFile: Extension of output file should be '%s'\n", ext);
    return NULL;
  }
  if ((fptr = fopen(name, mode)) == NULL) 
  {
    printf("openFile: Cannot open file '%s'\n", name);
    return NULL;
  }
  return fptr;
}


bool hasComment(char *line) 
{
  if (line == NULL) 
  {
    return false;
  }
  return strstr(line, COMMENT);
}


void ltrim(char *str) 
{
  int i = 0;

  while (isspace(str[i])) ++i;

  int len = strlen(str + i);

  strncpy(str, str + i, len);
  str[len] = '\0';
}


void rtrim(char *str) 
{
  int i = strlen(str) - 1;

  while(isspace(str[i])) --i;

  int len = i + 1;

  strncpy(str, str, len);
  str[len] = '\0';
}


void trim(char *str) 
{
  ltrim(str);
  rtrim(str);
}


void filterComment(char *line) 
{ 
  if (hasComment(line)) 
  {
    line = strtok(line, COMMENT);
    trim(line);
    strcat(line, "\n");
  }
}


void convertToBase2_16Bit(int val, char *res)
{
  int nBits = 16;
  strcpy(res, "0000000000000000");

  while (val > 0) 
  {
    int rem = val % 2;
    val /= 2;

    res[(--nBits)] = rem ? '1' : '0';
  }
}


int isRegA(char *instr) 
{
  return instr[0] == '@';
} 


char *handleRegAInstruction(char *str) 
{
  char *label = strtok(str + 1, "\n");
  int addr = getRAMAddressSymbol(label);
    
  if (addr != -1) 
  {
    convertToBase2_16Bit(addr, str);
  } 
  else 
  {
    convertToBase2_16Bit(pc, str);
  } 
  strcat(str, "\n");

  pc++;
  return str;
}


char *asmToBin(char *line) 
{
  if (isRegA(line)) 
  {
    line = realloc(line, sizeof(char) * 17);
    line = handleRegAInstruction(line);
  }
  else 
  {

  } 

  return line;
}


void translate(FILE *inputFile, FILE *outputFile) 
{
  int pc = 0;
  int buffSize = 1024 + 1;
  char *line = (char*)malloc(sizeof (char) * buffSize);
  line[(sizeof line / sizeof (char) - 1)] = '\0';

  while (fgets(line, buffSize, inputFile) != NULL) 
  {
    trim(line);
    strcat(line, "\n");

    if (line[0] != '/' && line[1] != '/') 
    {
      filterComment(line);

      bool isNotEmptyLine = strcmp(line, "\n") != 0;

      if (strlen(line) || isNotEmptyLine)
      {
        fputs(asmToBin(line), outputFile);
      }
    }
    
  }
  free(line);
}


int assemble(char *inputFileName, char *outputFileName) 
{
  FILE *inputFile = openFile(inputFileName, "r");
  FILE *outputFile = openFile(outputFileName, "w");

  if (inputFile != NULL && outputFile != NULL) 
  {
    translate(inputFile, outputFile);
  }
  
  fclose(inputFile);
  fclose(outputFile);
  return 1;
}