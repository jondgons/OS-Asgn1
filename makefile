#Name: Cody Gonsowski & Ethan Seiber
#File: makefile
#Desc: makefile for assignment #1

CC=gcc

DEBUG=-g

TARGET=shell

CFLAGS=-c -Wall $(DEBUG)

all: $(TARGET)

$(TARGET): shell.o
	$(CC) shell.o -0 $(TARGET)
	
shell.o: shell.c
	$(CC) $(CFLAGS) shell.c