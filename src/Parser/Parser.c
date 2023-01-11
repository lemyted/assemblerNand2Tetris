#include "Parser.h"
// #include "../Symbol/Symbol.h"

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