# Used as template for good practice
# https://www2.cs.duke.edu/courses/cps108/spring04/resources/makefiles/sample.html

CXX = g++

STD_VERSION = -std=c++17
DEBUG_LEVEL = -g
WARNINGS_ALL = -Wall
FSANITIZE_ADDRESS = -fsanitize=address
CXXFLAGS =  $(STD_VERSION) $(DEBUG_LEVEL) $(WARNINGS_ALL) $(FSANITIZE_ADDRESS)

OBJ_DIR = bin
SRC_DIR = src

SRC_FILES := $(wildcard $(SRC_DIR)/*/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(SRC_FILES:  $(SRC_DIR)/%.cpp = $(OBJ_DIR)/%.o)

library: $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^
.PHONY: clean

Serializable.o: Serializable.h

clean:
	rm -f $(OBJ_FILES) library



# SRC_FILES := $(wildcard $(SRC_DIR)/*/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)

# all : Library.out

# Library.out : $(OBJ_FILES)
# 	$(CXX) -o $@ $(OBJ_FILES) 

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
# 	mkdir -p $(@D)
# 	$(CXX) $(CXXFLAGS) -c -o $@ $< 
# # .cpp.o:
# #    $(CC) $(CFLAGS) -c $<`



# # Library: ./target/main.o
# # 	g++ ./target/main.o -o Library