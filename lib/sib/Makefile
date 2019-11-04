CC = gcc 
SRC += $(wildcard *.c)
OBJ += $(SRC:%.c=%.o)

INC += -I ./ 

exe:$(OBJ)
		

$(OBJ):$(SRC)
	 $(CC) $(subst .o,.c,$@) -o $@ -c $(INC)

.PHONY:clean
clean:
	$(RM) $(OBJ)
