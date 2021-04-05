ifndef EXAMPLE
	echo "Please define EXAMPLE"
	exit 1
endif

CC	= g++
DEFINES = -DINC=\"src/userfuncs/$(EXAMPLE).h\" -DOFILE=\"out/$(EXAMPLE).out\"
CFLAGS	= -g -O2 -std=c++03 -Wall -I. $(DEFINES)

SRCS	= src/aha.c

all: build/$(EXAMPLE)

build/objs/$(EXAMPLE).o: src/main.c src/userfuncs/$(EXAMPLE).h
	mkdir -p build/objs
	$(CC) -c $(CFLAGS) -o build/objs/$(EXAMPLE).o src/main.c

build/$(EXAMPLE): build/objs/$(EXAMPLE).o
	$(CC) $(CFLAGS) -o build/$(EXAMPLE) build/objs/$(EXAMPLE).o

clean:
	$(RM) -r build
