#!/usr/bin/env python

import serial
import sys
import getopt
import os
import time

device = "/dev/ttyUSB0"

try:
	opts, args = getopt.getopt(sys.argv[1:], "d:")
except getopt.GetoptError as err:
	print("usage: file_send.py [-d <device>]")
	sys.exit(2)

for opt, arg in opts:
	if opt == "-d":
		device = arg
		
#Вот здесь вот
tty = serial.Serial(device, 115200)

def sendFile(filename):
	sfile = open(filename, "rb")
	
	sfile.seek(0, os.SEEK_END)
	size = sfile.tell()
	sfile.seek(0, os.SEEK_SET)
	
	tty.write(str.encode("file_receive " + str(size) + " " + filename + "\n"))
	time.sleep(1)
	block = 32
	while size > 0:
		data = sfile.read(block if size > block else size)
		tty.write(data)
		time.sleep(0.025)
		size -= block
		print(size)
	
	sfile.close()

tty.write(b"cd /flash\n");
sendFile("sensors")
sendFile("export")
tty.write(b"ruc export sensors\n");

tty.close()
