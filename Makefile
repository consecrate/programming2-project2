CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Iinclude
TARGET ?= project2

SRC := $(wildcard src/*.cpp)
HEADERS := $(wildcard include/*.h)

.PHONY: all run check clean

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

check: $(TARGET)
	@echo "Build check passed: $(TARGET)"

clean:
	rm -f $(TARGET)
