CC = g++
FLAGS = -std=c++11 -g -c
LINK_LIB = -lgtest
ALL_HEADERS = src/JSONParser.h src/non_tml/NonTml.h src/non_tml/NonTmlAbstr.h src/token/Token.h \
src/token/TokenAbstract.h src/value/Value.h src/value/ValueAbstract.h src/types.h
TARGET = la_test
INCLUDE_PATH = -I /home/xzx/codes/JSON_Parser

# need automatical dependency generation

la_test: $(ALL_HEADERS) JSONParser.o lexical_analyzer_test.o ValueAbstract.o
	$(CC) JSONParser.o lexical_analyzer_test.o $(LINK_LIB) -o la_test

JSONParser.o: $(ALL_HEADERS) src/JSONParser.cpp
	$(CC) src/JSONParser.cpp $(FLAGS) $(INCLUDE_PATH)

lexical_analyzer_test.o: $(ALL_HEADERS)  test/lexical_analyzer_test.cpp
	$(CC) test/lexical_analyzer_test.cpp $(FLAGS) $(INCLUDE_PATH)

.PHONY:clean
clean:
	-rm $(TARGET) JSONParser.o lexical_analyzer_test.o

