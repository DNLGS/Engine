CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -pedantic
LDFLAGS := -Wl,-subsystem,console

SRCDIR := src src/window src/shader src/render src/dependencies/glad/src
INCDIR  := include
LIBDIR  := lib
BUILDDIR := build
BINDIR  := bin
TESTDIR := test

INCLUDES := -I$(INCDIR) -Isrc/dependencies/glad/include
TARGET  := $(BINDIR)/programa
SOURCES := $(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.c))
OBJECTS := $(patsubst %.c, $(BUILDDIR)/%.o, $(notdir $(SOURCES)))
LIBOBJS := $(wildcard $(LIBDIR)/*.c)
LIBS    := $(patsubst $(LIBDIR)/%.c, $(BUILDDIR)/lib%.a, $(LIBOBJS))
VPATH    := $(SRCDIR)

LDLIBS := -lopengl32 -lgdi32

all: dirs $(TARGET)

all: dirs
	@echo SOURCES = $(SOURCES)
	@echo OBJECTS = $(OBJECTS)

dirs:
	@if not exist $(BUILDDIR) mkdir $(BUILDDIR)
	@if not exist $(BINDIR) mkdir $(BINDIR)

build/glad.o: src/dependencies/glad/src/glad.c
	$(CC) $(CFLAGS) -Wno-pedantic $(INCLUDES) -c $< -o $@

$(BUILDDIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILDDIR)/lib%.a: $(LIBDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(BUILDDIR)/$*.o
	ar rcs $@ $(BUILDDIR)/$*.o

$(TARGET): $(OBJECTS) $(LIBS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

test: CFLAGS += -g -O0
test: $(TARGET)
	$(CC) $(CFLAGS) $(INCLUDES) $(TESTDIR)/*.c $(OBJECTS) -o $(BINDIR)/test_runner
	./$(BINDIR)/test_runner

clean:
	@if exist $(BUILDDIR) rmdir /s /q $(BUILDDIR)
	@if exist $(BINDIR) rmdir /s /q $(BINDIR)

distclean: clean
	@if exist $(LIBDIR) rmdir /s /q $(LIBDIR)

.PHONY: all dirs test clean distclean