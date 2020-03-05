default: decode

decode.o: decode.c 
	    gcc -c decode.c -o decode.o

snowboy-decode.o: snowboy-decode.c
		gcc -c snowboy-decode.c -o snowboy-decode.o

decode: decode.o snowboy-decode.o
	    gcc decode.o -o decode
		gcc snowboy-decode.o -o snowboy-decode

clean:
	    -rm -f decode.o
	    -rm -f decode
		-rm -f snowboy-decode
		-rm -f snowby-decode.o

