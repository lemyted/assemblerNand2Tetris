#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

int paramsOk(int argc, char* argv[]);

FILE *openFile(char* name, char *mode);

bool hasComment(char *line);

void ltrim(char *str);

void rtrim(char *str);

void trim(char *str);

void filterComment(char *line);

void convertToBase2_16Bit(int val, char *res);

int isRegA(char *instr);

struct FileContent 
{
  int numLines;
  char **lines;
};

struct FileContent *createFileContent();

int addLine(char *lineToAdd, struct FileContent *content);

void deleteFileContent(struct FileContent *table);

struct FileContent *readFile(FILE *name);