CC = gcc
CFLAGS = -Wall -O2
OBJS = main.o lda.o data_face80.o

all: lda_app

lda_app: $(OBJS)
	$(CC) $(CFLAGS) -o lda_app $(OBJS)

main.o: main.c lda.h data_face80.h
lda.o: lda.c lda.h
data_face80.o: data_face80.c data_face80.h

clean:
	rm -f *.o lda_app
