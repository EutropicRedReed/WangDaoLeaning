SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
ELF:=main
CC:=gcc
CFLAGS:=-g
$(ELF):$(OBJS)
	gcc $^ -o $@

clean:
	rm -rf $(OBJS) $(ELF)
