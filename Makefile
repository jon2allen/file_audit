CXX=g++
CXX_LLVM=clang++
CXX_WIN=cl
TARGET=file_audit

SRC_FILES=file_audit.cpp 
OBJ_FILES=$(patsubst %.cpp,%.o,$(SRC_FILES))

CFLAGS=-c -Wall -O2

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

$(TARGET).exe: $(OBJ_FILES)
	$(CXX_WIN) $(LFLAGS) $(OBJ_FILES) /Fe:$(TARGET).exe

%.o: %.cpp
	$(CXX) $(CFLAGS) $< -o $@

%.obj: %.cpp
	$(CXX_WIN) $(CFLAGS) $< /Fo$@

install:
	cp $(TARGET) /usr/local/bin/$(TARGET)

clean:
	rm -f $(OBJ_FILES) $(TARGET) $(TARGET).llvm $(TARGET).exe

