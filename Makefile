
CC = g++-10
L_SFML =  -lsfml-graphics -lsfml-window -lsfml-system 
INCLUDE_PATH = ./include
CFLAGS = -std=c++20 -Wall -Wextra -I${INCLUDE_PATH}
TARGET = tick-tack-toe

all: model view controller observer main link

link: 
	${CC} build/tmp/main.o build/tmp/model.o build/tmp/view.o build/tmp/controller.o build/tmp/observer.o  -o ${TARGET} ${CFLAGS} ${L_SFML}
	mv ${TARGET} ./build/${TARGET}

main: 
	${CC} ${CFLAGS} -c -g  src/main.cpp -o build/tmp/main.o 

model:
	${CC} ${CFLAGS} -c -g  src/model.cpp -o build/tmp/model.o 

view:
	${CC} ${CFLAGS} -c -g  src/view.cpp -o build/tmp/view.o 

controller:
	${CC} ${CFLAGS} -c -g  src/controller.cpp -o build/tmp/controller.o 

observer:
	${CC} ${CFLAGS} -c -g  src/observer.cpp -o build/tmp/observer.o 

run:
	./build/${TARGET}