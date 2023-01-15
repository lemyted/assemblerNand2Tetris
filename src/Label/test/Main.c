#include "LabelTest.h"

// isLabel
void test_validLabel_isLabel_returnTrue(void) 
{
  char str[] = "(MAIN)";
  CU_ASSERT_TRUE(isLabel(str));
}

void test_invalidLabel1_isLabel_returnFalse(void) 
{
  char str[] = "()";
  CU_ASSERT_FALSE(isLabel(str));
}

void test_invalidLabel2_isLabel_returnFalse(void) 
{
  char str[] = "(MAIN";
  CU_ASSERT_FALSE(isLabel(str));
}

void test_invalidLabel3_isLabel_returnFalse(void) 
{
  char str[] = "MAIN)";
  CU_ASSERT_FALSE(isLabel(str));
}

void test_nullLabel_isLabel_returnFalse(void) 
{
  char str[10];
  CU_ASSERT_FALSE(isLabel(str));
}


// createLabel
void test_validPrams_createLabel_keyValueValid(void) 
{
  struct Label *label = createLabel("key", 1);
  CU_ASSERT_STRING_EQUAL(label->key, "key");
  CU_ASSERT_EQUAL(label->value, 1);
  deleteLabel(label); 
}

void test_nullParams_createLabel_labelNull(void) 
{
  struct Label *label = createLabel(NULL, 0);
  CU_ASSERT_PTR_NULL(label);
}


// deleteLabel
void test_validLabel_deleteLabel_labelNull(void) 
{
  struct Label *label = createLabel("key", 1);
  CU_ASSERT_PTR_NOT_NULL(label);
  deleteLabel(label);
  CU_ASSERT_STRING_NOT_EQUAL(label->key, "key");
  CU_ASSERT_NOT_EQUAL(label->value, 1);
}


// createLabelTable
void test_createLableTable_tableValid(void) 
{
  struct LabelTable *table = createLabelTable();
  CU_ASSERT_EQUAL(table->length, 0);
  CU_ASSERT_PTR_NOT_NULL(table);
  deleteLabelTable(table);
}


// addLabel
void test_validLabel_addLabel_labelAdded(void) 
{
  char k1[] = "key1";
  int v1 = 1;
  char k2[] = "key2";
  int v2 = 2;
  struct LabelTable *table = createLabelTable();
  struct Label *label1 = createLabel(k1, v1);
  struct Label *label2 = createLabel(k2, v2);
  addLabel(label1, table);
  addLabel(label2, table);
  CU_ASSERT_EQUAL(table->length, 2);
  CU_ASSERT_STRING_EQUAL(table->labels[0]->key, k1);
  CU_ASSERT_EQUAL(table->labels[0]->value, v1);
  CU_ASSERT_STRING_EQUAL(table->labels[1]->key, k2);
  CU_ASSERT_EQUAL(table->labels[1]->value, v2);
  deleteLabelTable(table);
}

void test_nullLabel_addLabel_labelNotAdded(void) 
{
  struct LabelTable *table = createLabelTable();
  struct Label *label = NULL;
  int status = addLabel(label, table);
  CU_ASSERT_EQUAL(table->length, 0);
  CU_ASSERT_EQUAL(status, 1);
  deleteLabelTable(table);
}


// getLabel
void test_validkey_getLabel_returnLabel(void) 
{
  char k1[] = "key1";
  int v1 = 1;
  char k2[] = "key2";
  int v2 = 2;
  struct LabelTable *table = createLabelTable();
  struct Label *label1 = createLabel(k1, v1);
  struct Label *label2 = createLabel(k2, v2);
  addLabel(label1, table);
  addLabel(label2, table);
  struct Label *res1 = getLabel(k1, table);
  struct Label *res2 = getLabel(k2, table);
  CU_ASSERT_EQUAL(res1->value, v1);
  CU_ASSERT_EQUAL(res2->value, v2)
  deleteLabelTable(table);
}

void test_invalidKey_getLabel_returnNull(void) 
{
  char k1[] = "key1";
  int v1 = 1;
  char k2[] = "key2";
  int v2 = 2;
  struct LabelTable *table = createLabelTable();
  struct Label *label1 = createLabel(k1, v1);
  struct Label *label2 = createLabel(k2, v2);
  addLabel(label1, table);
  addLabel(label2, table);
  struct Label *res1 = getLabel("k3", table);
  struct Label *res2 = getLabel("k4", table);
  CU_ASSERT_PTR_NULL(res1);
  CU_ASSERT_PTR_NULL(res2);
  deleteLabelTable(table);
}


// removeLabel
void test_validLabel_removeLabel_labelRemoved(void) 
{
  char k1[] = "key1";
  int v1 = 1;
  char k2[] = "key2";
  int v2 = 2;
  struct LabelTable *table = createLabelTable();
  struct Label *label1 = createLabel(k1, v1);
  struct Label *label2 = createLabel(k2, v2);
  addLabel(label1, table);
  addLabel(label2, table);
  int status = removeLabel(k1, table);
  CU_ASSERT_EQUAL(status, 0);
  CU_ASSERT_STRING_EQUAL(table->labels[0]->key, k2);
  CU_ASSERT_EQUAL(table->length, 1);
  deleteLabelTable(table);
}

void test_inexistantLabel_removeLabel_labelNotRemoved(void) 
{
  char k1[] = "key1";
  int v1 = 1;
  char k2[] = "key2";
  int v2 = 2;
  struct LabelTable *table = createLabelTable();
  struct Label *label1 = createLabel(k1, v1);
  struct Label *label2 = createLabel(k2, v2);
  addLabel(label1, table);
  addLabel(label2, table);
  int status = removeLabel("k3", table);
  CU_ASSERT_EQUAL(status, 1);
  CU_ASSERT_EQUAL(table->length, 2);
  deleteLabelTable(table);
}


//deleteLabelTable
void test_validTable_deleteTable_tableDeleted(void) 
{
  struct LabelTable *table = createLabelTable();
  CU_ASSERT_EQUAL(table->length, 0);
  deleteLabelTable(table);
  CU_ASSERT_NOT_EQUAL(table->length, 0);
}

// removeParenthesesTestSuite
void test_strWithParentheses_removeParentheses_parenthesesRemoved(void) 
{
  char *str = (char*)malloc(sizeof(char) * 8);
  char s[] = "(hello)";
  strcpy(str, s);
  str[8] = '\0';
  CU_ASSERT_STRING_EQUAL(removeParentheses(str), "hello");
  free(str);
}

void manualDebug(void) 
{
  char *str = (char*)malloc(sizeof(char) * 8);
  str = "(hello)";
  CU_ASSERT_STRING_EQUAL(removeParentheses(str), "hello");
  free(str);
}

int main(int argc, char *argv[]) 
{
  //manualDebug();
  CU_initialize_registry();

  CU_pSuite isLabelTestSuite = CU_add_suite("isLabelTestSuite", NULL, NULL);
  CU_add_test(isLabelTestSuite, "test_validLabel_isLabel_returnTrue", test_validLabel_isLabel_returnTrue);
  CU_add_test(isLabelTestSuite, "test_invalidLabel1_isLabel_returnFalse", test_invalidLabel1_isLabel_returnFalse);
  CU_add_test(isLabelTestSuite, "test_invalidLabel2_isLabel_returnFalse", test_invalidLabel2_isLabel_returnFalse);
  CU_add_test(isLabelTestSuite, "test_invalidLabel3_isLabel_returnFalse", test_invalidLabel3_isLabel_returnFalse);
  CU_add_test(isLabelTestSuite, "test_nullLabel_isLabel_returnFalse", test_nullLabel_isLabel_returnFalse);

  CU_pSuite createLabelTestSuite = CU_add_suite("createLabelTestSuite", NULL, NULL);
  CU_add_test(createLabelTestSuite, "test_validPrams_createLabel_keyValueValid", test_validPrams_createLabel_keyValueValid);
  CU_add_test(createLabelTestSuite, "test_nullParams_createLabel_labelNull", test_nullParams_createLabel_labelNull);
  CU_add_test(createLabelTestSuite, "test_validLabel_deleteLabel_labelNull", test_validLabel_deleteLabel_labelNull);

  CU_pSuite createLabelTableTestSuite = CU_add_suite("createLabelTable", NULL, NULL);
  CU_add_test(createLabelTableTestSuite, "test_createLableTable_tableValid", test_createLableTable_tableValid);

  CU_pSuite addLabelTestSuite = CU_add_suite("addLabel", NULL, NULL);
  CU_add_test(addLabelTestSuite, "test_validLabel_addLabel_labelAdded", test_validLabel_addLabel_labelAdded);
  CU_add_test(addLabelTestSuite, "test_nullLabel_addLabel_labelNotAdded", test_nullLabel_addLabel_labelNotAdded);

  CU_pSuite getLabelTestSuite = CU_add_suite("getLabel", NULL, NULL);
  CU_add_test(getLabelTestSuite, "test_validkey_getLabel_returnLabel", test_validkey_getLabel_returnLabel);
  CU_add_test(getLabelTestSuite, "test_invalidKey_getLabel_returnNull", test_invalidKey_getLabel_returnNull);

  CU_pSuite removeLabelTestSuite = CU_add_suite("removeLabel", NULL, NULL);
  CU_add_test(removeLabelTestSuite, "test_validLabel_removeLabel_labelRemoved", test_validLabel_removeLabel_labelRemoved);
  CU_add_test(removeLabelTestSuite, "test_inexistantLabel_removeLabel_labelNotRemoved", test_inexistantLabel_removeLabel_labelNotRemoved);

  CU_pSuite deleteLabelTableTestSuite = CU_add_suite("deleteLabelTableTestSuite", NULL, NULL);
  CU_add_test(deleteLabelTableTestSuite, "test_validTable_deleteTable_tableDeleted", test_validTable_deleteTable_tableDeleted);

  CU_pSuite removeParenthesesTestSuite = CU_add_suite("removeParenthesesTestSuite", NULL, NULL);
  CU_add_test(removeParenthesesTestSuite, " test_strWithParentheses_removeParentheses_parenthesesRemoved",  test_strWithParentheses_removeParentheses_parenthesesRemoved);

  if (strcmp(argv[1], "-basic\n")) 
  {
    CU_basic_run_tests();
  }
  else 
  {
    CU_console_run_tests();
  }

  CU_cleanup_registry();
}