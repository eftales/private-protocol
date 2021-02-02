.PHONY: clean stop
all:
	gcc server/lscServer.c server/lsc.h server/lsc.c server/lscExtract.c server/lscExtract.h -o lscServer 
	gcc client/lscClient.c client/lsc.h client/lsc.c client/lscEncapsulate.c client/lscEncapsulate.h -o lscClient

clean: 
	rm -rf *.o lscServer lscClient serverMAC clientMAC
	
stop:
	pkill lscServer

