con_mysql:query.c delete.c insert.c update.c
	gcc query.c -o query -I /usr/include/mysql/ -lmysqlclient
	gcc delete.c -o delete -I /usr/include/mysql/ -lmysqlclient
	gcc insert.c -o insert -I /usr/include/mysql/ -lmysqlclient
	gcc update.c -o update -I /usr/include/mysql/ -lmysqlclient
clean:
	rm query delete insert update
