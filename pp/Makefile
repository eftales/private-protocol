.PHONY: clean stop
all:
	gcc ppServer.c pp.h pp.c ppExtract.c ppExtract.h -o ppServer 
	gcc ppClient.c pp.h pp.c ppEncapsulate.c ppEncapsulate.h -o ppClient

clean: 
	rm -rf *.o ppServer ppClient
	
stop:
	pkill ppServer

