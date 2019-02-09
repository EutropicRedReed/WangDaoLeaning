SRCS:=$(wildcard *.c)
TARGETS:=$(SRCS:%.c=%)
CFLAGS:=-lpthread
all:$(TARGETS)
	@for i in $(TARGETS);do gcc -o $${i} $${i}.c $(CFLAGS);done
clean:
	rm -rf $(TARGETS)

