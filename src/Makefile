#######################

src = $(wildcard *.c)
obj = $(src:%.c=%.o)

INC += -I ../lib/slog/
INC += -I ../lib/obex/
INC += -I ../lib/rfcomm/

libs += -lpthread
libs += -lm
libs += -lopenobex
libs += -lbluetooth

gdb += -g

MakefliePath_CJSON += ../lib/cJson/
MakefliePath_SLOG += ../lib/slog/
MakefliePath_OBEX += ../lib/obex/
MakefliePath_RFCOMM += ../lib/rfcomm/

LIB_OBJ += ../lib/cJson/cJSON.o 
LIB_OBJ += ../lib/slog/slog.o
LIB_OBJ += ../lib/obex/obex_io.o
LIB_OBJ += ../lib/obex/obex_test_client.o
LIB_OBJ += ../lib/obex/obex_test_server.o
LIB_OBJ += ../lib/obex/test.o
LIB_OBJ += ../lib/rfcomm/stRfcomm.o

EXE_TEST = exe
EXE = ../bin/exe

DDBUG_RDWR += -DRDWR 		# $(DDBUG_RDWR)
DDBUG_LISTEN += -DLISTEN 	# $(DDBUG_LISTEN)
DDBUG_TIMER += -DTIMER 		# $(DDBUG_TIMER)

exe:$(obj)
	$(CC) $(obj) -o $(EXE_TEST) $(LIB_OBJ) $(libs) $(INC) 
	#$(CC) $(obj) -o $(EXE) $(LIB_OBJ) $(libs) $(INC)
	$(RM) $(obj) 

$(obj):$(src)
	$(CC) $(subst .o,.c,$@) -o $@ -c $(INC) $(gdb)  $(DDBUG_RDWR) $(DDBUG_TIMER)

$(src):
	$(RM) $(LIB_OBJ) 
	$(MAKE) -C $(MakefliePath_CJSON)
	$(MAKE) -C $(MakefliePath_SLOG)
	$(MAKE) -C $(MakefliePath_OBEX)
	$(MAKE) -C $(MakefliePath_RFCOMM)

.PHONY:clean
clean:
	$(RM) $(EXE_TEST)

.PHONY:rmake
rmake:
	$(RM) $(LIB_OBJ) 
	$(MAKE) -C $(MakefliePath_CJSON)
	$(MAKE) -C $(MakefliePath_SLOG)
	$(MAKE) -C $(MakefliePath_OBEX)
	$(MAKE) -C $(MakefliePath_RFCOMM)

