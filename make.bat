mkdir build
g++ -g -I./include -I./test -c src/block.cpp -o build/block.o
g++ -g -I./include -I./test -c src/controller.cpp -o build/controller.o
g++ -g -I./include -I./test -c src/display.cpp -o build/display.o
g++ -g -I./include -I./test -c src/keyboard.cpp -o build/keyboard.o
g++ -g -I./include -I./test -c src/table.cpp -o build/table.o
g++ -g -I./include -I./test ./build/block.o  ./build/controller.o  ./build/display.o  ./build/keyboard.o  ./build/table.o main.cpp -o main