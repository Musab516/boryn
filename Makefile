CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra

SRC = src/main.cpp src/lexer.cpp src/parser.cpp src/interpreter.cpp
OUT = main.byn

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)

clean:
	rm -f $(OUT)
