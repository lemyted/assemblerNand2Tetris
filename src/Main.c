#include "Parser/Parser.h"
#include "Symbol/Symbol.h"
#include "Label/Label.h"

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
    // convertToBase2_16Bit(pc++, str);
  } 
  strcat(str, "\n");

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


int main(int argc, char* argv[]) 
{
  if (paramsOk(argc, argv)) 
  {
    assemble(argv[1], argv[2]);
  }
}