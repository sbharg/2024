# the compiler: gcc for C program, define as g++ for C++
CC = g++-14

# compiler flags:
#  -Wall  - this flag is used to turn on most compiler warnings
CFLAGS  = -Wall -O2 -std=c++20

# The build target 
TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

run: $(TARGET)
	./$(TARGET) input.txt

sample: $(TARGET)
	./$(TARGET) sample.txt

clean:
	$(RM) $(TARGET)