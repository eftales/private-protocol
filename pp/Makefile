.PHONY: clean stop
all:
	gcc server/ppServer.c server/pp.h server/pp.c server/ppExtract.c server/ppExtract.h -o ppServer 
	gcc client/ppClient.c client/pp.h client/pp.c client/ppEncapsulate.c client/ppEncapsulate.h -o ppClient

clean: 
	rm -rf *.o ppServer ppClient
	
stop:
	pkill ppServer

