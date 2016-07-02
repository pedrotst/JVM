CC = g++
CFLAGS = -I./include/ -g -std=c++11

########################## Geracao dos executaveis ##########################
jvm: classFile.o interpreter_op_code.o leitor.o little_to_big.o read_bytes.o exibidor.o read_attributes.o read_methods.o print_code.o interpretador.o frame.o jvm.o main.o verificador.o moveobj
	$(CC) $(CFLAGS) -o jvm.out ./obj/operationMap.o ./obj/classFile.o ./obj/interpreter_op_code.o ./obj/leitor.o ./obj/little_to_big.o ./obj/read_bytes.o ./obj/exibidor.o ./obj/read_attributes.o ./obj/read_methods.o ./obj/print_code.o ./obj/frame.o ./obj/interpretador.o ./obj/jvm.o ./obj/main.o ./obj/verificador.o

########################## Geracao dos .o ##########################
main.o:
	$(CC) $(CFLAGS) -c ./src/main.cpp

leitor.o:
	$(CC) $(CFLAGS) -c ./src/leitor.cpp

little_to_big.o:
	$(CC) $(CFLAGS) -c ./src/little_to_big.cpp

read_bytes.o:
	$(CC) $(CFLAGS) -c ./src/read_bytes.cpp

exibidor.o:
	$(CC) $(CFLAGS) -c ./src/exibidor.cpp ./src/operationMap.cpp

read_attributes.o:
	$(CC) $(CFLAGS) -c ./src/read_attributes.cpp

read_methods.o:
	$(CC) $(CFLAGS) -c ./src/read_methods.cpp

print_code.o:
	$(CC) $(CFLAGS) -c ./src/print_code.cpp

interpretador.o:
	$(CC) $(CFLAGS) -c ./src/interpretador.cpp

frame.o:
	$(CC) $(CFLAGS) -c ./src/frame.cpp

jvm.o:
	$(CC) $(CFLAGS) -c ./src/jvm.cpp

interpreter_op_code.o:
	$(CC) $(CFLAGS) -c ./src/interpreter_op_code.cpp

classFile.o:
	$(CC) $(CFLAGS) -c ./src/classFile.cpp

#translator.o:
	#$(CC) $(CFLAGS) -c ./src/op_instrucs.cpp

verificador.o:
	$(CC) $(CFLAGS) -c ./src/verificador.cpp

########################## Move e Clean ##########################
moveobj:
	mkdir -p ./obj
	mv ./*.o ./obj/

clean:
	rm ./obj/*.o
