#include "Label.h"
#include <stdio.h>

bool isLabel(char *str) 
{
  if (str[0] == '(' && str[1] != ')' && str != NULL) 
  {
    return strstr(str, ")");
  }
  return false;
}

struct Label *createLabel(char *key, char *value) 
{
  if (key == NULL || value == NULL) 
  {
    return NULL;
  }

  int lenKey = strlen(key);
  int lenValue = strlen(value);

  struct Label* label = (struct Label*)malloc(sizeof (struct Label));
  label->key = (char*)malloc(sizeof (char) * (lenKey + 1));
  label->value = (char*)malloc(sizeof (char) * (lenValue + 1));

  if (key != NULL && value != NULL) 
  {
    strcpy(label->key, key);
    strcpy(label->value, value);
  }

  return label;
}

void deleteLabel(struct Label* label) 
{
  if (label != NULL) 
  {
    free(label->key);
    free(label->value);
    free(label);
  }
}

struct LabelTable *createLabelTable() 
{
  struct LabelTable *labels = (struct LabelTable*)malloc(sizeof(struct LabelTable));
  labels->length = 0;
  return labels;
}

int addLabel(struct Label *toAdd, struct LabelTable *table) 
{
  if (toAdd == NULL || table == NULL) 
  {
    return 1;
  }

  table->labels = (struct Label**)realloc(table->labels, sizeof(struct Label*) * (++table->length));

  if (table->labels == NULL) 
  {
    return 1;
  }

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

    if (strcmp(current->key, key) == 0) 
    {
      return current; 
    }
  }
  return NULL;
}

int removeLabel(char *key, struct LabelTable *table) 
{
  if (table == NULL) 
  {
    return 1;
  }

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