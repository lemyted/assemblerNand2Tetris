#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool isLabel(char *str);

struct Label 
{
  char *key;
  char *value;
};

struct LabelTable 
{
  int length;
  struct Label* labels;
};

struct Label *createLabel(char *key, char *value);

void deleteLabel(struct Label* label);