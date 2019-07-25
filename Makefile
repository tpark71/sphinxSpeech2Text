default: decode

decode.o: decode.c 
	    gcc -c decode.c -o decode.o

decode: decode.o
	    gcc decode.o -o decode

clean:
	    -rm -f decode.o
	    -rm -f decode
