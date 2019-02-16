SRC:=$(wildcard *.c)
client:$(SRC)
	gcc $^ -o $@ -lpthread -g -lcrypt -I /usr/include/mysql/ -lmysqlclient -lcrypto -lssl
clean:
	rm client
