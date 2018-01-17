########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
EJS = p3_e1 p3_e2 p3_e3 p3_e4
########################################################
OBJECTSP3_E1 = p3_e1.o functions.o Node.o queue.o
OBJECTSP3_E2 = p3_e2.o functions.o Node.o queue.o graph.o
OBJECTSP3_E3 = p3_e3.o functionslist.o list.o
OBJECTSP3_E4 = p3_e4.o functionslist.o list.o Node.o graph-list.o
########################################################

all: $(EJS) clear

p3_e1: $(OBJECTSP3_E1)
	$(CC) $(CFLAGS) -o p3_e1 $(OBJECTSP3_E1)

p3_e2: $(OBJECTSP3_E2)
	$(CC) $(CFLAGS) -o p3_e2 $(OBJECTSP3_E2)

p3_e3: $(OBJECTSP3_E3)
	$(CC) $(CFLAGS) -o p3_e3 $(OBJECTSP3_E3)

p3_e4: $(OBJECTSP3_E4)
	$(CC) $(CFLAGS) -o p3_e4 $(OBJECTSP3_E4)

p3_e1.o: p3_e1.c Node.h queue.h
	$(CC) $(CFLAGS) -c p3_e1.c

p3_e2.o: p3_e2.c graph.h queue.h types.h
	$(CC) $(CFLAGS) -c p3_e2.c

p3_e3.o: p3_e3.c list.h
	$(CC) $(CFLAGS) -c p3_e3.c

p3_e4.o: p3_e4.c Node.h graph.h
	$(CC) $(CFLAGS) -c p3_e4.c

functions.o: functions.c Node.h
	$(CC) $(CFLAGS) -c functions.c

functionslist.o: functionslist.c functionslist.h
	$(CC) $(CFLAGS) -c functionslist.c

Node.o: Node.c Node.h types.h
	$(CC) $(CFLAGS) -c Node.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c

graph-list.o: graph-list.c graph.h list.h
	$(CC) $(CFLAGS) -c graph-list.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p3_e1"
	./p3_e1

	@echo ">>>>>>Running p3_e2"
	./p3_e2

	@echo ">>>>>>Running p3_e3"
	./p3_e3

	@echo ">>>>>>Running p3_e4"
	./p3_e4

runv:
	@echo ">>>>>>Running p3_e1 with valgrind"
	valgrind --leak-check=full ./p3_e1

	@echo ">>>>>>Running p3_e2 with valgrind"
	valgrind --leak-check=full ./p3_e2

	@echo ">>>>>>Running p3_e3 with valgrind"
	valgrind --leak-check=full ./p3_e3

	@echo ">>>>>>Running p3_e4 with valgrind"
	valgrind --leak-check=full ./p3_e4
