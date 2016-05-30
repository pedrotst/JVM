CC = g++
CFLAGS = -I./include/ -g

########################## Geracao dos executaveis ##########################
leitor: leitor.o little_to_big.o moveobj
	$(CC) $(CFLAGS) -o leitor ./obj/leitor.o ./obj/little_to_big.o

########################## Geracao dos .o ##########################
leitor.o:
	$(CC) $(CFLAGS) -c ./src/leitor.cpp

little_to_big.o:
	$(CC) $(CFLAGS) -c ./src/little_to_big.cpp

########################## Move e Clean ##########################
moveobj:
	mv ./*.o ./obj/

clean:
	rm ./obj/*.o
