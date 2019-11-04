#######################
#==========
CC = gcc
SRC += $(wildcard *.c)
OBJ += $(SRC:%.c=%.o)

INC += -I../lib/slog/
INC += -IcJson/
LIBS += -lpthread
LIBS += -lm
GDB += -g

MakefliePath += cJson/
CJSON_OBJ += cJson/cJSON.o

EXE_TEST = exe

$(EXE_TEST):$(OBJ)
	$(CC) $(OBJ) -o $(EXE_TEST) $(CJSON_OBJ)  $(LIBS) $(GDB) $(INC)
	$(RM) $(OBJ) 

$(OBJ):$(SRC)
	$(MAKE) -C $(MakefliePath)
	$(CC) $(subst .o,.c,$@) -o $@ -c $(INC) 

	
.PHONY:clean
clean:
	$(RM) exe