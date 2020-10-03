CC = g++
FLAGS = -std=c++11 -g -c
LINK_LIB = -lgtest
ALL_HEADERS = src/JSONParser.h src/NonTml.h src/NonTmlAbstr.h src/Token.h src/TokenAbstract.h src/types.h
TARGET = la_test

# need automatical dependency generation

la_test: $(ALL_HEADERS) JSONParser.o lexical_analyzer_test.o
	$(CC) JSONParser.o lexical_analyzer_test.o $(LINK_LIB) -o la_test

JSONParser.o: $(ALL_HEADERS) src/JSONParser.cpp
	$(CC) src/JSONParser.cpp $(FLAGS)

lexical_analyzer_test.o: $(ALL_HEADERS)  test/lexical_analyzer_test.cpp
	$(CC) test/lexical_analyzer_test.cpp $(FLAGS)

.PHONY:clean
clean:
	-rm $(TARGET) JSONParser.o lexical_analyzer_test.o

