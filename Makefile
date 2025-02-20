TARGET=WordFrequencyChecker
CC=gcc
CFLAGS=-g
SRC=src/main.c src/binarySearch.c src/FNV1a.c \
	src/hashTable.c src/linearSearch.c src/textTools.c \
	src/item.c
OBJS=$(SRC:src/%.c=obj/%.o)

all: clear $(TARGET)

$(TARGET):$(OBJS)
	mkdir -p bin
	$(CC) $(CFLAGS) -o bin/$(TARGET) $(OBJS)

obj/%.o:src/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c -MMD -MP $< -o $@

-include $(OBJS:.o=.d)

clear:
	rm -rf obj
