CC = g++
LIBS = -lm -pthread
CFLAGS = -Wall -c -fPIC -O3 -fomit-frame-pointer -ffast-math -DREENTRANT -std=c++0x
#CFLAGS = -Wall -c -fPIC -g -DREENTRANT -std=c++0x
PROGFLAGS = $(LIBS) -fPIC -O3 -fomit-frame-pointer -ffast-math -DREENTRANT
#PROGFLAGS = $(LIBS) -fPIC -g -DREENTRANT

EXE = eval
OBJ = eval.o
NAM = eval

all: clean $(OBJ)
	$(CC) $(PROGFLAGS) $(OBJ) -o $(EXE)

$(NAM).o: $(NAM).h $(NAM).cpp
	$(CC) $(CFLAGS) $(NAM).cpp -o $(NAM).o

clean:
	rm -f .*.swp *~ $(OBJ) $(EXE)

backup:
	tar -cvzf backups/`date +%Y-%m-%d-%H.%M`.tar.gz *.h *.cpp Makefile 

run:
	./eval
