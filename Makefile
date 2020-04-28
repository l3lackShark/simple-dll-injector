# This Makefile will build the application.

# Object files to create for the executable
OBJS = obj/injector.o

# Warnings to be raised by the C compiler
WARNS = -Wall

# Names of tools to use when building
CC = gcc
EXE = injector.exe

CFLAGS = -std=c99

# Linker flags
LDFLAGS = -lgdi32 -luser32 -lshlwapi -Wl,--subsystem,windows

.PHONY: all clean

# Build executable by default
all: executable

# strip symbols for release
release: LDFLAGS += -Os -s
release: executable

debug: CFLAGS += -Og
debug: exectuable

executable: bin/${EXE}

# Delete all build output
clean:
	cmd /c if exist bin\${EXE}  del /q bin\${EXE}
	cmd /c if exist obj\*  del /q obj\*

# Create build output directories if they don't exist
bin obj:
	cmd /c IF NOT EXIST "$@" mkdir "$@"

# Compile object files for executable
obj/%.o: src/%.c | obj
	${CC} ${CFLAGS} -c "$<" -o "$@"

# Build the exectuable
bin/${EXE}: ${OBJS} | bin
	${CC} -o "$@" ${OBJS} ${LDFLAGS}