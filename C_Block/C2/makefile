all: ticTacToeResult

.outputFolder:
	mkdir -p out
	
ticTacToeResult: .outputFolder
	clang -std=c++17 -lstdc++ -lm ticTacToeResult.cpp -Wall -Wextra -Werror -o out/ticTacToeResult
	./out/ticTacToeResult
