#include "Parser/Parser.h"

int main(int argc, char* argv[]) 
{
  if (paramsOk(argc, argv)) 
  {
    assemble(argv[1], argv[2]);
  }
}