proj7 : gfash2-proj7.o Pieces.o Exceptions.o Board.o Board.h Exceptions.h Pieces.h
	g++ -g -o proj7 gfash2-proj7.o Pieces.o Exceptions.o Board.o 


.cpp.o :
	g++ -g -c $<
