#######################
#==========
CC = gcc
SRC += $(wildcard *.c)
OBJ += $(SRC:%.c=%.o)


LIBS += -lm
LIBS += -lpthread
GDB += -g

EXE_TEST += main

$(EXE_TEST):$(OBJ)
	
tar:$(OBJ)
	$(CC) $(OBJ) -o $(EXE_TEST) $(LIBS) 

$(OBJ):$(SRC)
	$(CC) $(subst .o,.c,$@) -o $@ -c $(INC) $(GDB) 

	
.PHONY:clean
clean:
	$(RM) $(OBJ)
	$(RM) $(EXE_TEST) 
