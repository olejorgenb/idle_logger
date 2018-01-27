#!/usr/bin/env python2

import sys

def gettime(line):
	return int(line.split(" ")[1])

for line in sys.stdin:
	time = gettime(line)
	if time <= 1*60000:
		pass # ignore
	else:
		m = line.split(" ")
		print line,

	
		

