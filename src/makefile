CC	= gcc
CFLAGS	= -Wall -I../include
LDFLAGS	= -L../lib -lev3dev-c
OBJ	= main.o

RPATH	= ../start_robo

$(RPATH) : $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean :
	rm $(RPATH) *.o

all : $(RPATH)
