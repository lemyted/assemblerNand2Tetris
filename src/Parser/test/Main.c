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


// createFileContent
void test_createFileContent_returnValidFileContent(void) 
{
  struct FileContent *content = createFileContent();
  CU_ASSERT_PTR_NOT_EQUAL(content, NULL);
  CU_ASSERT_EQUAL(content->numLines, 0);
  deleteFileContent(content);
}


// addLine
void test_validPrams_createFileContent_lineAdded(void) 
{
  struct FileContent *content = createFileContent();
  char line1[] = "hello";
  char line2[] = "world";
  addLine(line1, content);
  addLine(line2, content);
  CU_ASSERT_EQUAL(content->numLines, 2);
  CU_ASSERT_STRING_EQUAL(content->lines[0], line1);
  CU_ASSERT_STRING_EQUAL(content->lines[1], line2);
  deleteFileContent(content);
}


// deleteFileContent
void test_validFileContent_deleteFileContent_fileContentDeleted(void) 
{
  struct FileContent *content = createFileContent();
  char line1[] = "hello";
  char line2[] = "world";
  addLine(line1, content);
  addLine(line2, content);
  deleteFileContent(content);
  CU_ASSERT_NOT_EQUAL(content->numLines, 2);
}


// readFile
void test_validFile_readFile_validResult(void) 
{
  FILE *file = openFile("resources/Parser.txt", "r");
  struct FileContent *content = readFile(file);
  CU_ASSERT_PTR_NOT_NULL(content);
  CU_ASSERT_EQUAL(content->numLines, 9);
  deleteFileContent(content);
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

  CU_pSuite createFileContentTestSuite = CU_add_suite("createFileContent", NULL, NULL);
  CU_add_test(createFileContentTestSuite, "test_createFileContent_returnValidFileContent", test_createFileContent_returnValidFileContent); 

  CU_pSuite addLineTestSuite = CU_add_suite("addLineTestSuite", NULL, NULL);
  CU_add_test(addLineTestSuite, "test_validPrams_createFileContent_lineAdded", test_validPrams_createFileContent_lineAdded);

  CU_pSuite deleteFileContentTestSuite = CU_add_suite("deleteFileContentTestSuite", NULL, NULL);
  CU_add_test(deleteFileContentTestSuite, "test_validFileContent_deleteFileContent_fileContentDeleted", test_validFileContent_deleteFileContent_fileContentDeleted);

  CU_pSuite readFileTestSuite = CU_add_suite("readFileTestSuite", NULL, NULL);
  CU_add_test(readFileTestSuite, "test_validFile_readFile_validResult", test_validFile_readFile_validResult);

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