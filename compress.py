#!/usr/bin/env python2

# Is a daylight time savings bug here somewhere (2014-03-31)

import sys

def gettime(line):
	return int(line.split(" ")[1])

line = sys.stdin.readline()
sys.stdout.write(line)

m = line.strip().split(" ")

previous_idle_time = int(m[1])
previous_timestamp = int(m[0])
previous_line = line

computer_off_addition = 0

for line in sys.stdin:
	m = line.strip().split(" ")
	try:
		timestamp = int(m[0])
		idle_time = int(m[1])
		timestamp_delta = timestamp - previous_timestamp
		if timestamp_delta >= 120:
			# computer been off
			print previous_timestamp, previous_idle_time
			computer_off_addition = timestamp_delta*1000
		elif idle_time > previous_idle_time:
			pass # ignore
		else:
			print previous_timestamp, previous_idle_time + computer_off_addition,
			if computer_off_addition > 0:
				print "computer_off"
			else:
				print

			computer_off_addition = 0
		previous_timestamp = timestamp
		previous_idle_time = idle_time
		previous_line = line
	except:
	       sys.stderr.write("error "+line+"\n")

sys.stdout.write(previous_line)
	
		

