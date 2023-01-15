#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool isLabel(char *str);

struct Label 
{
  char *key;
  int value;
};

struct LabelTable 
{
  int length;
  struct Label **labels;
};

struct Label *createLabel(char *key, int value);

void deleteLabel(struct Label *label);

struct LabelTable *createLabelTable();

int addLabel(struct Label *toAdd, struct LabelTable *table);

struct Label *getLabel(char *key, struct LabelTable *table);

int removeLabel(char *key, struct LabelTable *table);

void deleteLabelTable(struct LabelTable *table);

char *removeParentheses(char *line);