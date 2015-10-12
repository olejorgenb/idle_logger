#include <X11/Xlib.h>
#include <X11/extensions/scrnsaver.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/* in seconds */
#define POLL_INTERVAL   5

int main() {
	int event;
	int error;
	Display *dpy = XOpenDisplay(NULL);
	Drawable whatever = DefaultRootWindow(dpy);
	XScreenSaverInfo *info = NULL;

	if(XScreenSaverQueryExtension(dpy, &event, &error) == False) {
		exit(0);
	}

	while(1) {
		sleep(POLL_INTERVAL);
		info = XScreenSaverAllocInfo();
		XScreenSaverQueryInfo(dpy, whatever, info);

		printf("%lu %lu %lu\n", (unsigned long) time(NULL), info->idle, info->kind);

		XFree(info); /* or should I reuse it? */
	}
}

