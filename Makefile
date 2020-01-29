
CC = g++
L_SFML =  -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS = -std=c++14 -Wall  ${L_SFML} -g
TARGET = xo

all: model view controller observer main link

link: 
	${CC} ofiles/main.o ofiles/model.o ofiles/view.o ofiles/controller.o ofiles/observer.o  -o ${TARGET} ${L_SFML} 
	mv ${TARGET} ./build/${TARGET}

main: 
	${CC} ${CFLAGS} -c -g  main.cpp -o ofiles/main.o 

model:
	${CC} ${CFLAGS} -c -g  model.cpp -o ofiles/model.o 

view:
	${CC} ${CFLAGS} -c -g  view.cpp -o ofiles/view.o 

controller:
	${CC} ${CFLAGS} -c -g  controller.cpp -o ofiles/controller.o 

observer:
	${CC} ${CFLAGS} -c -g  observer.cpp -o ofiles/observer.o 

run:
	./build/${TARGET}