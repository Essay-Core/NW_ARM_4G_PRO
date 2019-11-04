CC = gcc 
SRC += $(wildcard *.c)
OBJ += $(SRC:%.c=%.o)

LIB += -lopenobex

exe:$(OBJ)
		

$(OBJ):$(SRC)
	 $(CC) $(subst .o,.c,$@) -o $@ -c $(LIB)

.PHONY:clean
clean:
	$(RM) $(OBJ)
