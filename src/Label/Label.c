#include "Label.h"

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
  free(label->key);
  free(label->value);
  free(label);
}