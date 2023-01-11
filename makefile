SYMBOL_MODULE=./src/Symbol/Symbol.c
SYMBOL_TEST_MODULE=$(SYMBOL_MODULE) ./src/Symbol/test/Main.c
SYMBOL_TEST_NAME=SymbolTest

LABEL_MODULE=./src/Label/Label.c
LABEL_TEST_MODULE=$(LABEL_MODULE) ./src/Label/test/Main.c
LABEL_TEST_NAME=LabelTest

PARSER_MODULE=./src/Parser/Parser.c
PARSER_TEST_MODULE=$(PARSER_MODULE) ./src/Parser/test/Main.c
PARSER_TEST_NAME=ParserTest

BIN=assembler
REMOVE_FILE_IF_EXISTS=rm -f ./${BIN}

main:
	$(REMOVE_FILE_IF_EXISTS)
	gcc ./src/Main.c $(PARSER_MODULE) $(SYMBOL_MODULE) $(LABEL_MODULE) -o $(BIN)
debug:
	$(REMOVE_FILE_IF_EXISTS)
	gcc ./src/Main.c $(PARSER_MODULE) -g -o $(BIN)
	gdb --args $(BIN) input/Mult.asm output/Prog.hack

testParserConsole:
	gcc $(PARSER_TEST_MODULE) -o ./tests/$(PARSER_TEST_NAME) -lcunit
	./tests/$(PARSER_TEST_NAME)
testParserBasic:
	gcc $(PARSER_TEST_MODULE) -o ./tests/$(PARSER_TEST_NAME) -lcunit
	./tests/$(PARSER_TEST_NAME) -basic

testSymbolConsole:
	gcc $(SYMBOL_TEST_MODULE) -o ./tests/$(SYMBOL_TEST_NAME) -lcunit
	./tests/$(SYMBOL_TEST_NAME)
testSymbolBasic:
	gcc $(SYMBOL_TEST_MODULE) -o ./tests/$(SYMBOL_TEST_NAME) -lcunit
	./tests/$(SYMBOL_TEST_NAME) -basic

testLabelConsole:
	gcc $(LABEL_TEST_MODULE) -o ./tests/$(LABEL_TEST_NAME) -lcunit
	./tests/$(LABEL_TEST_NAME)
testLabelBasic:
	gcc $(LABEL_TEST_MODULE) -o ./tests/$(LABEL_TEST_NAME) -lcunit
	./tests/$(LABEL_TEST_NAME) -basic
testLabelDebug:
	gcc $(LABEL_TEST_MODULE) -o ./tests/$(LABEL_TEST_NAME) -lcunit -g
	gdb --args ./tests/$(LABEL_TEST_NAME)