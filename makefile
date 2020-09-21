CC = g++
INCLUDE = ./Mya/Main.cpp ./Mya/Mya/* ./Mya/Wrappers/*
INCLUDES = -I./lib/include
LIBS = -L./lib/lib
CFLAGS = -std=c++17
LDFLAGS =
OUTPUT =

BUILD_NUMBER_FILE=build-number.txt

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
else ifeq ($(UNAME_S),MSYS_NT-10.0)
	INCLUDES += -I./windows_lib/include -IC:/VulkanSDK/1.2.148.1/Include
	LIBS += -L./windows_lib/lib -LC:/VulkanSDK/1.2.148.1/Lib
	LDFLAGS += -w -lmingw32 -lSDL2main -lSDL2 -llua -lvulkan-1
	OUTPUT = ./build_windows/Mya
endif

mya: $(BUILD_NUMBER_FILE)
	$(CC) $(CFLAGS) $(INCLUDE) $(BUILD_NUMBER_LDFLAGS) $(INCLUDES) $(LIBS) $(LDFLAGS) -o $(OUTPUT)

run: 
	$(OUTPUT).exe

include buildnumber.mk