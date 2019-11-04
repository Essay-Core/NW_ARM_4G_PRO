#######################
#==========
CC = gcc
SRC += $(wildcard *.c)
OBJ += $(SRC:%.c=%.o)


LIBS += -lm
GDB += -g


EXE_TEST = exe

$(EXE_TEST):$(OBJ)
	

$(OBJ):$(SRC)
	$(CC) $(subst .o,.c,$@) -o $@ -c $(INC) 

	
.PHONY:clean
clean:
	$(RM) exe