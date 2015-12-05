MPI_HOME    = /users/faculty/snell/mpich
MPI_INCL        = $(MPI_HOME)/include
MPI_LIB         = $(MPI_HOME)/lib

TARGET     	= final-project
SRC   			= src/job.c src/main.c src/server.c src/util.c src/worker.c src/calculate.c
OBJ         = job.o main.o server.o util.o worker.o calculate.o
DEPS        = src/job.h src/node.h src/server.h src/util.h src/worker.h src/calculate.h

CC         		= $(MPI_HOME)/bin/mpicc
CFLAGS			  = -O -I$(MPI_INCL)
LFLAGS     		= -L$(MPI_LIB) -lm -lmpich

%.o: src/%.c $(DEPS) 
	 	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS)

run: $(TARGET)
	/bin/rm -f PI* && $(MPI_HOME)/bin/mpirun -np 16 -machinefile $(TARGET).machines $(TARGET)

clean:
		/bin/rm -f  *.o && /bin/rm -f $(TARGET)
