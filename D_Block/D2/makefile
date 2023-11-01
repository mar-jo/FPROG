all: BucketSort InsertionSort BubbleSort SelectionSort QuickSort

.outputFolder:
	mkdir -p ./out
	
BucketSort: .outputFolder
	g++ -std=c++20 -lm Mark\ 1/BucketSort.cpp -Wall -Wextra -Werror -o ./out/BucketSort
	./out/BucketSort

InsertionSort: .outputFolder
	g++ -std=c++20 -lm Mark\ 2/InsertionSort.cpp -Wall -Wextra -Werror -o ./out/InsertionSort
	./out/InsertionSort

BubbleSort: .outputFolder
	g++ -std=c++20 -lm Mark\ 3/BubbleSort.cpp -Wall -Wextra -Werror -o ./out/BubbleSort
	./out/BubbleSort

SelectionSort: .outputFolder
	g++ -std=c++20 -lm Mark\ 4/SelectionSort.cpp -Wall -Wextra -Werror -o ./out/SelectionSort
	./out/SelectionSort

QuickSort: .outputFolder
	g++ -std=c++20 -lm Mark\ 5/QuickSort.cpp -Wall -Wextra -Werror -o ./out/QuickSort
	./out/QuickSort