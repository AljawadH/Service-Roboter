CC	= arm-linux-gnueabi-gcc
CFLAGS	= -Wall -Werror -I../include
LDFLAGS	= -L../lib -lev3dev-c -Wl,-rpath ../lib
OBJ	= main.o pen.o movement.o gyro_ctrl.o

RPATH	= start_robo

$(RPATH) : $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean :
	rm $(RPATH) *.o

all : $(RPATH)
