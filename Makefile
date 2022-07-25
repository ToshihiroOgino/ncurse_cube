# https://minus9d.hatenablog.com/entry/2017/10/20/222901
CC := gcc

TARGET := Game.exe

CYGWINDIR := C:/cygwin64/bin
TARGETDIR := bin
BUILDDIR := $(TARGETDIR)/obj
SRCDIR := src

SRCEXT := .c
HEDEXT := .h
OBJEXT := .o

INCLUDE := -I./include
CFLAGS := -Wall
LDFLAGS := -lcurses

ifeq ($(OS),Windows_NT)
	FINDPATH := $(CYGWINDIR)/find.exe
else
	FINDPATH := find
endif

sources := $(shell $(FINDPATH) $(SRCDIR) -type f -name *$(SRCEXT))
objects := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(subst $(SRCEXT),$(OBJEXT),$(sources)))

main: directories $(TARGETDIR)/$(TARGET)

directories:
	@mkdir -p $(BUILDDIR)

$(TARGETDIR)/$(TARGET): $(objects)
	$(CC) -o $(TARGETDIR)/$(TARGET) $^ $(LDFLAGS)

$(BUILDDIR)/%$(OBJEXT): $(SRCDIR)/%$(SRCEXT)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	@rm -rf $(BUILDDIR)
