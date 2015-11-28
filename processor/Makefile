MPI_HOME    = /users/faculty/snell/mpich
MPI_INCL        = $(MPI_HOME)/include
MPI_LIB         = $(MPI_HOME)/lib

TARGET     	= final-project
SRC   			= src/main.c src/server.c src/util.c src/worker.c
OBJ         = main.o server.o util.o worker.o
DEPS        = src/node.h src/server.h src/util.h src/worker.h

CC         		= $(MPI_HOME)/bin/mpicc
CFLAGS			  = -O -I$(MPI_INCL)
LFLAGS     		= -L$(MPI_LIB) -lm -lmpich

%.o: src/%.c $(DEPS) 
	 	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS)

run: $(TARGET)
	/bin/rm -f PI* && $(MPI_HOME)/bin/mpirun -np 2 -machinefile $(TARGET).machines $(TARGET)

clean:
		/bin/rm -f  *.o && /bin/rm -f $(TARGET)
