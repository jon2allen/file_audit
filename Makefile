CXX=g++
CXX_LLVM=clang++
CXX_WIN=cl
TARGET=file_audit

SRC_FILES=file_audit.cpp
OBJ_FILES=file_audit.o
OBJ_FILES=$(patsubst %.cpp,%.o,$(SRC_FILES))
OBJ_FILES_WIN=$(patsubst %.cpp,%.obj,$(SRC_FILES))

CFLAGS=-c -Wall -O2
LFLAGS=-Wall # Set your linker flags here

WINCFLAGS=/std:c++20

.PHONY: all clean install

all: linux macos windows

linux: $(TARGET)

macos: $(TARGET).llvm

freebsd: $(TARGET).llvm

windows: $(TARGET).exe

$(TARGET): $(OBJ_FILES)
	$(CXX) $(LFLAGS) $(OBJ_FILES) -o $(TARGET)

$(TARGET).llvm:
	$(CXX_LLVM) $(CFLAGS) file_audit.cpp -o file_audit.o
	$(CXX_LLVM) $(LFLAGS) file_audit.o -o $(TARGET)

$(TARGET).exe: $(OBJ_FILES_WIN)
	$(CXX_WIN) $(WINCFLAGS) $(OBJ_FILES_WIN) /Fe:$(TARGET).exe

install:
	cp $(TARGET) /usr/local/bin/$(TARGET)

clean:
	rm -f $(OBJ_FILES) $(TARGET) $(TARGET).llvm $(TARGET).exe

