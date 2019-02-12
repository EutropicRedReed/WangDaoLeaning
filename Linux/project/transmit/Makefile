SRC:=$(wildcard *.c)
server:$(SRC)
	gcc $^ -o $@ -lpthread -g -lcrypt -I /usr/include/mysql/ -lmysqlclient
clean:
	rm thread_pool_server
