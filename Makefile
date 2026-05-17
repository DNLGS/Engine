# Compilador e flags
CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -pedantic
LDFLAGS :=
LDLIBS  :=

# Diretórios
SRCDIR  := src
INCDIR  := include
LIBDIR  := lib
BUILDDIR := build
BINDIR  := bin
TESTDIR := test

# Arquivos
TARGET  := $(BINDIR)/programa
SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))
LIBOBJS := $(wildcard $(LIBDIR)/*.c)
LIBS    := $(patsubst $(LIBDIR)/%.c, $(BUILDDIR)/lib%.a, $(LIBOBJS))

# Cabeçalhos
INCLUDES := -I$(INCDIR)

# Regra principal
all: dirs $(TARGET)

# Criar diretórios se não existirem
dirs:
	@mkdir -p $(BUILDDIR) $(BINDIR)

# Compilar .c da src/ para .o na build/
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compilar .c da lib/ para biblioteca estática
$(BUILDDIR)/lib%.a: $(LIBDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(BUILDDIR)/$*.o
	ar rcs $@ $(BUILDDIR)/$*.o

# Linkar executável
$(TARGET): $(OBJECTS) $(LIBS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

# Compilar testes
test: CFLAGS += -g -O0
test: $(TARGET)
	$(CC) $(CFLAGS) $(INCLUDES) $(TESTDIR)/*.c $(OBJECTS) -o $(BINDIR)/test_runner
	./$(BINDIR)/test_runner

# Limpar arquivos gerados
clean:
	rm -rf $(BUILDDIR) $(BINDIR)

# Limpar tudo (incluindo bibliotecas compiladas)
distclean: clean
	rm -rf $(LIBDIR)/*.a

# Não tratar nomes de diretório como alvos
.PHONY: all dirs test clean distclean