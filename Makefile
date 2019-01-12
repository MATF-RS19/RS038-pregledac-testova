CC = g++
CFLAGS = -g
SRCS = main.cpp image_processing.cpp handler.cpp
PROG = pregledac

OPENCV = `pkg-config opencv --cflags --libs`
LIBS = $(OPENCV)

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

.PHONY: clean

clean:
	rm *.o *.~ $(PROG)
