TARGET=WordFrequencyChecker
CC=gcc
SRC=src/main.c src/binarySearch.c src/FNV1a.c \
	 src/hashTable.c src/linearSearch.c src/textTools.c
OBJS=$(SRC:src/%.c=obj/%.o)

all: clear $(TARGET)

$(TARGET):$(OBJS)
	mkdir -p bin
	$(CC) -g -o bin/$(TARGET) $(OBJS)

obj/%.o:src/%.c
	mkdir -p obj
	$(CC) -c -MMD -MP $< -o $@

-include $(OBJS:.o=.d)

clear:
	rm -rf obj	
