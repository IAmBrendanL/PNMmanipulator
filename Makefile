SRC=PNMmanipulator.C image.C sink.C source.C PNMreader.C PNMwriter.C filters.C logging.C 
OBJ=$(SRC:.C=.o)

prog: $(OBJ)
	g++ $(OBJ) -o PNM\ Manipulator 

.C.o: $<
	g++  -g -I. -c $<

clean:
	rm *.o  PNM\ Manipulator 
