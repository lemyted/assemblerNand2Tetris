#include "Parser/Parser.h"
#include "Symbol/Symbol.h"
#include "Label/Label.h"

struct LabelTable *getLabels(struct FileContent *content);

char *handleRegAInstruction(char *str, struct LabelTable *table);

char *asmToBin(char *line, struct LabelTable *table);

void translate(FILE *inputFile, FILE *outputFile);

int assemble(char *inputFileName, char *outputFileName);