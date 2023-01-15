#include "Main.h"

struct LabelTable *getLabels(struct FileContent *content) 
{
  if (content == NULL) return NULL;

  struct LabelTable *table = createLabelTable();

  for (int pc = 0; pc < content->numLines; pc++) 
  {
    char *line = content->lines[pc];
    trim(line);

    if (isLabel(line)) 
    {
      struct Label *label = createLabel(removeParentheses(line), pc); 
      addLabel(label, table);
    }
  }
  return table;
}

char *handleRegAInstruction(char *str, struct LabelTable *table) 
{
  char *label = strtok(str + 1, "\n");
  int addr = getRAMAddressSymbol(label);
    
  if (addr != -1) 
  {
    convertToBase2_16Bit(addr, str);
  } 
  else 
  {
    convertToBase2_16Bit(getLabel(label, table)->value, str);
  } 
  strcat(str, "\n");

  return str;
}


char *asmToBin(char *line, struct LabelTable *table) 
{
  if (isRegA(line)) 
  {
    line = realloc(line, sizeof(char) * 17);
    line = handleRegAInstruction(line, table);
  }
  else 
  {

  } 

  return line;
}


void translate(FILE *inputFile, FILE *outputFile) 
{
  struct FileContent *content = readFile(inputFile);
  struct LabelTable *table = getLabels(content);

  for (int i = 0; i < content->numLines; i++) 
  {
    char *line = content->lines[i];
    trim(line);
    strcat(line, "\n");

    if (line[0] != '/' && line[1] != '/') 
    {
      filterComment(line);
      bool isNotEmptyLine = strcmp(line, "\n") != 0;

      if (strlen(line) && isNotEmptyLine)
      {
        fputs(asmToBin(line, table), outputFile);
      }
    }
  }
  deleteLabelTable(table);
  deleteFileContent(content);
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