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


struct FileContent *createFileContent() 
{
  struct FileContent *content = (struct FileContent*)malloc(sizeof(struct FileContent));
  content->numLines = 0;
  return content;
}


int addLine(char *lineToAdd, struct FileContent *content) 
{
  if (lineToAdd == NULL || content == NULL) return 1;
  
  content->lines = (char**)realloc(content->lines, sizeof(char*) * (++content->numLines));

  if (content->lines == NULL) return 1;

  int len = strlen(lineToAdd);
  char *currentLine = (char*)malloc(sizeof (char) * len + 1);
  memcpy(currentLine, lineToAdd, sizeof (char) * len);
  currentLine[len] = '\0';

  content->lines[((content->numLines - 1))] = currentLine;
  return 0;
}


void deleteFileContent(struct FileContent *content) 
{
  for (int i = 0; i < content->numLines; i++) 
  {
    free(content->lines[i]);
  }
  free(content->lines);
  free(content);
}


struct FileContent *readFile(FILE *file)
{
  struct FileContent *content = createFileContent();
  int buffSize = 1024 + 1;
  char *tmp = (char*)malloc(sizeof (char) * buffSize);
  tmp[(buffSize - 1)] = '\0';

  if (tmp == NULL || content == NULL) return NULL;

  while (fgets(tmp, buffSize, file) != NULL) 
  {
    addLine(tmp, content);
  }

  free(tmp);
  return content;
}