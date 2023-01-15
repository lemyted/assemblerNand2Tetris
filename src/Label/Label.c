#include "Label.h"
#include <stdio.h>

bool isLabel(char *str) 
{
  if (str[0] == '(' && str[1] != ')' && str != NULL) 
  {
    return str[(strlen(str) - 1)] == ')';
  }
  return false;
}

struct Label *createLabel(char *key, int value) 
{
  if (key == NULL) return NULL;

  int lenKey = strlen(key);
  struct Label* label = (struct Label*)malloc(sizeof (struct Label));
  label->key = (char*)malloc(sizeof (char) * (lenKey + 1));

  if (key != NULL) 
  {
    strcpy(label->key, key);
    label->value = value;
  }

  return label;
}

void deleteLabel(struct Label* label) 
{
  if (label != NULL) 
  {
    free(label->key);
    free(label);
  }
}

struct LabelTable *createLabelTable() 
{
  struct LabelTable *table = (struct LabelTable*)malloc(sizeof(struct LabelTable));
  table->length = 0;
  return table;
}

int addLabel(struct Label *toAdd, struct LabelTable *table) 
{
  if (toAdd == NULL || table == NULL) return 1;

  table->labels = (struct Label**)realloc(table->labels, sizeof(struct Label*) * (++table->length));

  if (table->labels == NULL) return 1;

  int i = (table->length - 1);
  struct Label *currentLabel = (struct Label*)malloc(sizeof (struct Label));
  memcpy(currentLabel, toAdd, sizeof (struct Label));
  table->labels[i] = currentLabel;
  return 0;
}

struct Label *getLabel(char *key, struct LabelTable *table) 
{
  for (int i = 0; i < table->length; i++)
  {
    struct Label *current = table->labels[i];

    if (strcmp(current->key, key) == 0) return current; 
  }
  return NULL;
}

int removeLabel(char *key, struct LabelTable *table) 
{
  if (table == NULL) return 1;

  bool isFound = false;

  for (int i = 0, j = 0; i < table->length; i++) 
  {
    if (strcmp(table->labels[i]->key, key) != 0) 
    {
      table->labels[(j++)] = table->labels[i];
    } 
    else 
    {
      isFound = true;
    }
  }

  if (isFound) 
  {
    table->labels = (struct Label**)realloc(table->labels, sizeof(struct Label*) * (--table->length));
  }

  if(getLabel(key, table) == NULL && isFound == true) 
  {
    return 0;
  }
  return 1;
}

void deleteLabelTable(struct LabelTable *table) 
{
  for (int i = 0; i < table->length; i++) 
  {
    deleteLabel(table->labels[i]);
  }
  if (table->length > 0) 
  {
    free(table->labels);
  }
  free(table);
}

char *removeParentheses(char *line) 
{
  int newLen = strlen(line) - 2; // remove both parentheses

  for (int i = 0; line[i] != '\0'; i++) 
  {
    line[i] = line[(i+1)];
  }

  line[newLen] = '\0';
  line = (char*)realloc(line, sizeof (char) * (newLen + 1));
  return line;
}