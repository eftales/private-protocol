.PHONY: clean stop
all:
	gcc ppServer.c pp.h pp.c ppExtract.c ppExtract.h -o ppServer 

clean: 
	rm -rf *.o ppServer serverMAC
	
stop:
	pkill ppServer
