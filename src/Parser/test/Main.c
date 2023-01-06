#include "ParserTest.h"

// paramsOkTest
void test_paramsValid_paramsOk_true(void)
{
  char *input[] = { "main", "input/Mult.asm", "output/Prog.hack" };
  CU_ASSERT_TRUE(paramsOk(3, input));
}

void test_paramsOnly2_paramsOk_false(void)
{
  char *input[] = { "main", "input/Mult.asm" };
  CU_ASSERT_FALSE(paramsOk(2, input));
}

void test_paramsOnly1_paramsOk_false(void)
{
  char *input[] = { "main" };
  CU_ASSERT_FALSE(paramsOk(1, input));
}


// openFile 
  

// hasComment
void test_strHasNoComment_hasComment_false(void) 
{
  CU_ASSERT_FALSE(hasComment("hello"));
}

void test_strHasComment_hasComment_true(void)
{
  CU_ASSERT_TRUE(hasComment("hello // world"));
}

void test_strIsComment_hasComment_true(void) 
{
  CU_ASSERT_TRUE(hasComment("//hello world"));
}

void test_strIsNull_hasComment_false(void) 
{
  CU_ASSERT_FALSE(hasComment(NULL));
}


// trim
void test_strFrontSpace_trimFront(void) 
{
  char str[] = " hello";
  trim(str);
  CU_ASSERT_STRING_EQUAL(str, "hello");
}

void test_strBackSpace_trimBack(void) 
{
  char str[] = "hello ";
  trim(str);
  CU_ASSERT_STRING_EQUAL(str, "hello");
}

void test_strFrontAndBackSpace_trimBoth(void) 
{
  char str[] = " hello ";
  trim(str);
  CU_ASSERT_STRING_EQUAL(str, "hello");
}

void test_strSpaceInBetweenAndOutside_trimOutside(void) 
{
  char str[] = " hello world ";
  trim(str);
  CU_ASSERT_STRING_EQUAL(str, "hello world");
}


// filterComment
void test_strHasComment_filterComment_strHasNoComment(void) 
{
  char str[] = "hello //world";
  filterComment(str);
  CU_ASSERT_STRING_EQUAL(str, "hello\n");
}

void test_strHasNoComment_filterComment_strIsSame(void) 
{
  char str[] = "hello world";
  filterComment(str);
  CU_ASSERT_STRING_EQUAL(str, "hello world");
}


// convertToBase2_16Bit_16Bit
void test_decimalInt0_convertToBase2_16Bit_binaryStr(void) 
{
  int num = 0;
  char *line = (char*)malloc(sizeof (char ) * 1024);
  convertToBase2_16Bit(num, line);
  CU_ASSERT_STRING_EQUAL(line, "0000000000000000");
  free(line);
}

void test_decimalInt1_convertToBase2_16Bit_binaryStr(void) 
{
  int num = 1;
  char bin[16];
  convertToBase2_16Bit(num, bin);
  CU_ASSERT_STRING_EQUAL(bin, "0000000000000001");
}

void test_decimalInt12345_convertToBase2_16Bit_binaryStr(void) 
{
  int num = 12345;
  char bin[16];
  convertToBase2_16Bit(num, bin);
  CU_ASSERT_STRING_EQUAL(bin, "0011000000111001");
}


// isRegA
void test_regAInstruction_isRegA_true(void) 
{
  CU_ASSERT_TRUE(isRegA("@R2"));
}

void test_notRegAInstruction_isRegA_false(void) 
{
  CU_ASSERT_FALSE(isRegA("0;JMP"));
}


int main(int argc, char *argv[]) 
{
  CU_initialize_registry();

  CU_pSuite paramsOkTestSuite = CU_add_suite("paramsOkTestSuite", NULL, NULL);
  CU_add_test(paramsOkTestSuite, "test_paramsValid_paramsOk_true", test_paramsValid_paramsOk_true);
  CU_add_test(paramsOkTestSuite, "test_paramsOnly2_paramsOk_false", test_paramsOnly2_paramsOk_false);
  CU_add_test(paramsOkTestSuite, "test_paramsOnly1_paramsOk_false", test_paramsOnly1_paramsOk_false);

  CU_pSuite hasCommentTestSuite = CU_add_suite("hasCommentTest", NULL, NULL);
  CU_add_test(hasCommentTestSuite, "test_strHasNoComment_hasComment_false", test_strHasNoComment_hasComment_false);
  CU_add_test(hasCommentTestSuite, "test_strHasComment_hasComment_true", test_strHasComment_hasComment_true);
  CU_add_test(hasCommentTestSuite, "test_strIsComment_hasComment_true", test_strIsComment_hasComment_true);
  CU_add_test(hasCommentTestSuite, "test_strIsNull_hasComment_false", test_strIsNull_hasComment_false);

  CU_pSuite trimTestSuite = CU_add_suite("trimTestSuite", NULL, NULL);
  CU_add_test(trimTestSuite, "test_strFrontSpace_trimFront", test_strFrontSpace_trimFront);
  CU_add_test(trimTestSuite, "test_strBackSpace_trimBack", test_strBackSpace_trimBack);
  CU_add_test(trimTestSuite, "test_strFrontAndBackSpace_trimBoth", test_strFrontAndBackSpace_trimBoth);
  CU_add_test(trimTestSuite, "test_strSpaceInBetweenAndOutside_trimOutside", test_strSpaceInBetweenAndOutside_trimOutside);

  CU_pSuite filterCommentTestSuite = CU_add_suite("filterCommentTestSuite", NULL, NULL);
  CU_add_test(filterCommentTestSuite, "test_strHasComment_filterComment_strHasNoComment", test_strHasComment_filterComment_strHasNoComment);
  CU_add_test(filterCommentTestSuite, "test_strHasNoComment_filterComment_strIsSame", test_strHasNoComment_filterComment_strIsSame);

  CU_pSuite convertToBase2_16BitTestSuite = CU_add_suite("convertToBase2_16BitTestSuite", NULL, NULL);
  CU_add_test(convertToBase2_16BitTestSuite, "test_decimalInt0_convertToBase2_16Bit_binaryStr", test_decimalInt0_convertToBase2_16Bit_binaryStr);
  CU_add_test(convertToBase2_16BitTestSuite, "test_decimalInt1_convertToBase2_16Bit_binaryStr", test_decimalInt1_convertToBase2_16Bit_binaryStr);
  CU_add_test(convertToBase2_16BitTestSuite, "test_decimalInt12345_convertToBase2_16Bit_binaryStr", test_decimalInt12345_convertToBase2_16Bit_binaryStr);

  CU_pSuite isRegATestSuite = CU_add_suite("isRegATestSuite", NULL, NULL);
  CU_add_test(isRegATestSuite, "test_regAInstruction_isRegA_true", test_regAInstruction_isRegA_true);
  CU_add_test(isRegATestSuite, "test_notRegAInstruction_isRegA_false", test_notRegAInstruction_isRegA_false);

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