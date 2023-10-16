all: Monads

.outputFolder:
	mkdir -p out
	
Monads: .outputFolder
	clang -std=c++17 -lstdc++ -lm Monads.cpp -Wall -Wextra -Werror -o out/Monads
	./out/Monads
