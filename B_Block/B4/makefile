all: BucketSort InsertionSort BubbleSort SelectionSort QuickSort

.outputFolder:
	mkdir -p ./out
	
BucketSort: .outputFolder
	clang -std=c++17 -lstdc++ -lm Mark\ 1/BucketSort.cpp -Wall -Wextra -Werror -o ./out/BucketSort
	./out/BucketSort

InsertionSort: .outputFolder
	clang -std=c++17 -lstdc++ -lm Mark\ 2/InsertionSort.cpp -Wall -Wextra -Werror -o ./out/InsertionSort
	./out/InsertionSort

BubbleSort: .outputFolder
	clang -std=c++17 -lstdc++ -lm Mark\ 3/BubbleSort.cpp -Wall -Wextra -Werror -o ./out/BubbleSort
	./out/BubbleSort

SelectionSort: .outputFolder
	clang -std=c++17 -lstdc++ -lm Mark\ 4/SelectionSort.cpp -Wall -Wextra -Werror -o ./out/SelectionSort
	./out/SelectionSort

QuickSort: .outputFolder
	clang -std=c++17 -lstdc++ -lm Mark\ 5/QuickSort.cpp -Wall -Wextra -Werror -o ./out/QuickSort
	./out/QuickSort