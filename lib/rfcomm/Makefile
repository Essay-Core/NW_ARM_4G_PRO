CC = gcc 
SRC += $(wildcard *.c)
OBJ += $(SRC:%.c=%.o)

LIB += -lbluetooth

exe:$(OBJ)
		

$(OBJ):$(SRC)
	 $(CC) $(subst .o,.c,$@) -o $@ -c $(LIB)

.PHONY:clean
clean:
	$(RM) $(OBJ)
