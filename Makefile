all:
	gcc -std=gnu99 -lXss -lX11 idle_logger.c -o idle_logger
	gcc -std=gnu99 -lXss -lX11 idle.c -o idle

install:
	mkdir $(out)/bin
	cp idle_logger $(out)/bin


