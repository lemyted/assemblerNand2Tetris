#include "Main.h"

int main(int argc, char *argv[]) 
{
  //manualDebug();
  CU_initialize_registry();

  

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