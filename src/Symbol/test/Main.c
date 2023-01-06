#include "SymbolTest.h"
 
// getLengthSymbols
void test_lengthTestSymbols21_getLengthSymbols_returns21(void) 
{
  CU_ASSERT_EQUAL(getLengthSymbols(), 21);
}

//getRAMAddressSymbol
void test_inputSP_getRAMAddressSymbol_return0(void) 
{
  CU_ASSERT_EQUAL(getRAMAddressSymbol("SP"), 0);
}

int main(int argc, char *argv[]) 
{
  CU_initialize_registry();

  CU_pSuite getLengthSymbolsTestSuite = CU_add_suite("getLengthSymbolsTestSuite", NULL, NULL);
  CU_add_test(getLengthSymbolsTestSuite, "test_lengthTestSymbols21_getLengthSymbols_returns21", test_lengthTestSymbols21_getLengthSymbols_returns21);

  CU_pSuite getRAMAddressSymbolTestSuite = CU_add_suite("getRAMAddressSymbolTestSuite", NULL, NULL);
  CU_add_test(getRAMAddressSymbolTestSuite, "test_inputSP_getRAMAddressSymbol_return0", test_inputSP_getRAMAddressSymbol_return0);

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