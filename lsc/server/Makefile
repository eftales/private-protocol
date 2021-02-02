.PHONY: clean stop
all:
	gcc lscServer.c lsc.h lsc.c lscExtract.c lscExtract.h -o lscServer 

clean: 
	rm -rf *.o lscServer serverMAC
	
stop:
	pkill lscServer
