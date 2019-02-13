con_mysql:query.c delete.c insert.c update.c
	gcc table_three_query.c -o query -I /usr/include/mysql/ -lmysqlclient
	gcc table_three_delete.c -o delete -I /usr/include/mysql/ -lmysqlclient
	gcc table_three_insert.c -o insert -I /usr/include/mysql/ -lmysqlclient
	gcc table_three_update.c -o update -I /usr/include/mysql/ -lmysqlclient
clean:
	rm query delete insert update
