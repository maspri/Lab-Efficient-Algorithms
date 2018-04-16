#makefile

CC=g++
JC=javac

CFLAGS=-g -Wall
BUILDDIR := build 

CPP_SOURCE=$(wildcard *.cpp)
CPP_MAIN=$(CPP_SOURCE:.cpp=)
JAVA_SOURCE=$(wildcard *.java)
JAVA_CLASS=$(JAVA_SOURCE:.java=.class)

.PHONY: directories

all:  directories $(CPP_MAIN) $(JAVA_CLASS)

directories: $(BUILDDIR)

$(JAVA_CLASS): $(JAVA_SOURCE)
	$(JC) $(JAVA_SOURCE) -d $(BUILDDIR)

$(CPP_MAIN): $(CPP_SOURCE)
	$(CC) $(CFLAGS) $(CPP_SOURCE) -o $@
	@mv $@ $(BUILDDIR)


$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

clean:
	@echo "Removing Contents of \"build\""
	@rm $(BUILDDIR)/*

print:
	@echo $(CPP_MAIN)
