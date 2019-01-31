CC:=gcc
SRCS := $(wildcard *.c)
BINS := $(SRCS:%.c=%)
LINKERFLAG := -lpthread
CFLAGS:=-Wall
all: ${BINS}

%: %.c
	${CC} $< -o $@ $(CFLAGS) ${LINKERFLAG}
clean:
	rm -rf $(BINS) $(BINS).o $(BINS).s $(BINS).i
