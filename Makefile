# $@表示目标 ，$^表示所有依赖，$<表示依赖中的第一个
#预处理器标志，也就是预处理时的参数-I，-E。(如头文件的位置)
CPPFLAGS= -Iinclude
#编译时的参数 -C，-g，-Wall
CFLAGS= -O2 -g
#加载时的参数（如共享库）
LDFLAGS=
VPATH= src
CC=gcc

#表示除了当前目录，还有src目录下也有.c文件
src=$(wildcard *.c) $(wildcard src/*.c)
obj=$(patsubst %.c,%.o, $(src))
target=app

$(target):$(obj)
	$(CC) $^ $(LDFLAGS) -o $@

%.o:%.c
	$(CC) -c $^ $(CPPFLAGS) $(CFLAGS) -o $@

.PHONY: clean
clean:
	-rm -f *.o
	-rm -f $(target)
