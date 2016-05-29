#include <X11/Xlib.h>
#include <X11/extensions/scrnsaver.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/* in seconds */

#define POLL_INTERVAL   60
#define FLUSH_INTERVAL  60*1

#define BUFFER_SIZE    FLUSH_INTERVAL / POLL_INTERVAL

static const char *log_file_path = "/home/ole/log/idle_log.log";

/* The buffer contains a sequence of timestamp,idle_time. Ie. even indices contains the timestamp
   and odd contains the idle_time. */
static unsigned long buffer[BUFFER_SIZE*2];

void flush_log() {
	FILE *file = fopen(log_file_path, "a");
	for(int i = 0; i < BUFFER_SIZE; i++) {
		fprintf(file, "%lu %lu\n", buffer[i*2], buffer[i*2 + 1]);
	}
	fclose(file);
}

void config() {
	char* path = getenv("BRONNER_IDLE_LOGGER_PATH");
	if(path) {
	/* if ( access( path, W_OK ) == -1 ) { */
	/*	 fprintf(stderr, "%s doesn't exist or is unwritable. (specified in the env var BRONNER_IDLE_LOGGER_PATH)", path); */
	/*	 exit(1); */
	/* } */
	log_file_path = path;
	}
}


int main() {
	config();
	int counter = 0;
	int event;
	int error;
	Display *dpy = XOpenDisplay(NULL);
	if(!dpy) {
		fprintf(stderr, "Could not open display");
	}
	Drawable whatever = DefaultRootWindow(dpy);
	XScreenSaverInfo *info = NULL;

	if(XScreenSaverQueryExtension(dpy, &event, &error) == False) {
		exit(0);
	}
	while(1) {
		sleep(POLL_INTERVAL);
		info = XScreenSaverAllocInfo();
		XScreenSaverQueryInfo(dpy, whatever, info);

		buffer[counter*2] = (unsigned long) time(NULL);
		buffer[counter*2 + 1] = info->idle;

		XFree(info); /* or should I reuse it? */
		counter++;
		if(counter >= BUFFER_SIZE) {
			flush_log();
			counter = 0;
		}
	}
}

