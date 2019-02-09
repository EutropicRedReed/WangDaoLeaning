SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
ELF:=main
CC:=gcc
CFLAGS:=-g -Wall -Werror
#LIBFUNSCO:=libfunc.so
#CFLAGS:=-fpic
$(ELF):$(OBJS)
	gcc $^ -o $@  
clean:
	rm -rf $(OBJS) $(ELF)

