CC = g++
CFLAGS = -I./include/ -g

########################## Geracao dos executaveis ##########################
leitor: leitor.o little_to_big.o read_bytes.o exibidor.o read_attributes.o read_methods.o moveobj
	$(CC) $(CFLAGS) -o leitor ./obj/leitor.o ./obj/little_to_big.o ./obj/read_bytes.o ./obj/exibidor.o ./obj/read_attributes.o ./obj/read_methods.o

########################## Geracao dos .o ##########################
leitor.o:
	$(CC) $(CFLAGS) -c ./src/leitor.cpp

little_to_big.o:
	$(CC) $(CFLAGS) -c ./src/little_to_big.cpp

read_bytes.o:
	$(CC) $(CFLAGS) -c ./src/read_bytes.cpp

exibidor.o:
	$(CC) $(CFLAGS) -c ./src/exibidor.cpp

read_attributes.o:
	$(CC) $(CFLAGS) -c ./src/read_attributes.cpp

read_methods.o:
	$(CC) $(CFLAGS) -c ./src/read_methods.cpp

########################## Move e Clean ##########################
moveobj:
	mkdir -p ./obj
	mv ./*.o ./obj/

clean:
	rm ./obj/*.o
