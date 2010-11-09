all:
	gcc -std=gnu99 -lXss -lX11 *.c -o idle_logger

