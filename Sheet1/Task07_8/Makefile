#makefile

CC=g++
JC=javac

CFLAGS=-g -Wall -O2
BUILDDIR := build 

CPP_SOURCE=$(wildcard main.cpp)
CPP_SOURCE2=main
JAVA_SOURCE=$(wildcard main.java)
JAVA_SOURCE2=$(JAVA_SOURCE:.java=.class)

.PHONY: directories

all:  directories $(CPP_SOURCE2) $(JAVA_SOURCE2)

directories: $(BUILDDIR)

main.class: main.java
	$(JC) main.java -d $(BUILDDIR)

main: $(CPP_SOURCE)
	$(CC) $(CFLAGS) $(CPP_SOURCE) -o $@
	@mv $@ $(BUILDDIR)


$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

clean:
	@echo "Removing Contents of \"build\""
	@rm $(BUILDDIR)/*
