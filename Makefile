CXX=g++
CXX_LLVM=clang++
CXX_WIN=cl
TARGET=file_audit

SRC_FILES=file_audit.cpp 
OBJ_FILES=$(patsubst %.cpp,%.o,$(SRC_FILES))
OBJ_FILES_WIN=$(patsubst %.cpp,%.obj,$(SRC_FILES))

CFLAGS=-c  -Wall -O2

WINCFLAGS=/std:c++20

OBJ_SUFFIX=.o


.PHONY: all clean install

all: linux macos windows

linux: $(TARGET)
	
macos: $(TARGET).llvm

windows: $(TARGET).exe

$(TARGET): $(OBJ_FILES)
	$(CXX) $(LFLAGS) $(OBJ_FILES) -o $(TARGET)

$(TARGET).llvm: $(OBJ_FILES)
	$(CXX_LLVM) $(LFLAGS) $(OBJ_FILES) -o $(TARGET)

$(TARGET).exe: $(OBJ_FILES_WIN)
	$(CXX_WIN) $(WINCFLAGS) $(OBJ_FILES_WIN) /Fe:$(TARGET).exe

%.o: %.cpp
	$(CXX) $(CFLAGS) $< -o $@

%.obj: %.cpp
	$(CXX_WIN) $(WINCFLAGS) $< /Fo$@

install:
	cp $(TARGET) /usr/local/bin/$(TARGET)

clean:
	rm -f $(OBJ_FILES) $(TARGET) $(TARGET).llvm $(TARGET).exe

