all: SumMonad, InvertMatrixMonad, QuadraticSolutionMonad, IntegerDivision, ASCIIReader

.outputFolder:
	mkdir -p out
	
SumMonad: .outputFolder
	clang -std=c++17 -lstdc++ -lm SumMonad.cpp -Wall -Wextra -Werror -o out/SumMonad
	./out/SumMonad

InvertMatrixMonad: .outputFolder
	clang -std=c++17 -lstdc++ -lm InvertMatrixMonad.cpp -Wall -Wextra -Werror -o out/InvertMatrixMonad
	./out/InvertMatrixMonad

QuadraticSolutionMonad: .outputFolder
	clang -std=c++17 -lstdc++ -lm QuadraticSolutionMonad.cpp -Wall -Wextra -Werror -o out/QuadraticSolutionMonad
	./out/QuadraticSolutionMonad

IntegerDivision: .outputFolder
	clang -std=c++17 -lstdc++ -lm IntegerDivision.cpp -Wall -Wextra -Werror -o out/IntegerDivision
	./out/IntegerDivision

ASCIIReader: .outputFolder
	clang -std=c++17 -lstdc++ -lm ASCIIReader.cpp -Wall -Wextra -Werror -o out/ASCIIReader
	./out/ASCIIReader