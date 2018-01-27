#!/usr/bin/env python2

import sys
import datetime as dt

for line in sys.stdin:
	m = line.strip().split(" ")
	timestamp = int(m[0])
	idle_time = int(m[1])
	end = dt.datetime.fromtimestamp(timestamp)
	try:
		begin = end - dt.timedelta(seconds=idle_time/1000)
	except OverflowError:
		sys.stderr.write(str(idle_time/1000))
		break
	format_str = "%d.%m.%y %H:%M"
	print "%s\t%s\t%s\t%s" %  \
            (begin.strftime(format_str), 
                    end.strftime(format_str),
                    (end-begin),
                    "" if len(m) == 2 else m[2])
	
