#######################
#==========
CC = gcc
SRC += $(wildcard *.c)
OBJ += $(SRC:%.c=%.o)


LIBS += -lm
LIBS += -lpthread
GDB += -g


$(EXE_TEST):$(OBJ)
	
tar:$(OBJ)
	$(CC) $(OBJ) -o main $(LIBS) 

$(OBJ):$(SRC)
	$(CC) $(subst .o,.c,$@) -o $@ -c $(INC) $(GDB) 

	
.PHONY:clean
clean:
	$(RM) $(OBJ)
