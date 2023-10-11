all: MoodleShit

.outputFolder:
	mkdir -p out
	
MoodleShit: .outputFolder
	clang -std=c++17 -lstdc++ -lm MoodleShit.cpp -Wall -Wextra -Werror -o out/MoodleShit
	./out/MoodleShit
