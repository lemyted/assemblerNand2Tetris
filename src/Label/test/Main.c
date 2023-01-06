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
void test_createLabel_keyValueValid(void) 
{
  struct Label *label = createLabel("key", "value");
  CU_ASSERT_EQUAL(label->key, "key");
  CU_ASSERT_EQUAL(label->value, "value");
  deleteLabel(label); 
}

void manualDebug(void) 
{
  struct Label *label = createLabel("key", "value");
  CU_ASSERT_EQUAL(label->key, "key");
  CU_ASSERT_EQUAL(label->value, "value");
  deleteLabel(label);
}

int main(int argc, char *argv[]) 
{
  manualDebug();

  CU_initialize_registry();

  CU_pSuite isLabelTestSuite = CU_add_suite("isLabelTestSuite", NULL, NULL);
  CU_add_test(isLabelTestSuite, "test_validLabel_isLabel_returnTrue", test_validLabel_isLabel_returnTrue);
  CU_add_test(isLabelTestSuite, "test_invalidLabel1_isLabel_returnFalse", test_invalidLabel1_isLabel_returnFalse);
  CU_add_test(isLabelTestSuite, "test_invalidLabel2_isLabel_returnFalse", test_invalidLabel2_isLabel_returnFalse);
  CU_add_test(isLabelTestSuite, "test_invalidLabel3_isLabel_returnFalse", test_invalidLabel3_isLabel_returnFalse);
  CU_add_test(isLabelTestSuite, "test_nullLabel_isLabel_returnFalse", test_nullLabel_isLabel_returnFalse);

  CU_pSuite createLabelTestSuite = CU_add_suite("createLabelTestSuite", NULL, NULL);
  CU_add_test(createLabelTestSuite, "test_createLabel_keyValueValid", test_createLabel_keyValueValid);

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