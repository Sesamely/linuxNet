
CC = gcc
CFLAGS = -Isub -Iadd -O2
VPATH = add:sub:.
OBJS = add_int.o add_float.o sub_int.o sub_float.o main.o
TARGET = cacu
RM = rm -f
OBJDIR = objs

${TARGET}: ${OBJS}
	${CC} ${CFLAGS} -o $@ $^

clean:
	-${RM} ${OBJS}

realclean: clean
	-${RM} ${TARGET}
