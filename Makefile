OUTPUT_FILE = main

clean:
	@echo "Cleaning workplace..."
	rm ${OUTPUT_FILE}

build:
	@echo "Building the project..."
	g++ --std=c++11 -o ${OUTPUT_FILE} main.cpp -I./Tokenizer/ -I./Tokenizer/Token -I./Lexer/ -I./Lexer/Lexem Lexer/Lexem/Lexem.cpp Lexer/Lexer.cpp Tokenizer/Tokenizer.cpp Tokenizer/Token/Token.cpp

run:
	./${OUTPUT_FILE} test.txt