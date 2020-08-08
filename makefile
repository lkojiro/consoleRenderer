CXX = g++
CXXFLAGS = -Wall -g
all: out
	echo build done

out: render.o screen.o primitives.o pixel.o
	$(CXX) $(CXXFLAGS) -o out render.o screen.o pixel.o primitives.o

render.o: render.cpp screen.h primitives.h
	$(CXX) $(CXXFLAGS) -c render.cpp

screen.o: screen.h primitives.h pixel.h

primitives.o: primitives.h

pixel.o: pixel.h

clean:
	rm out *.o
	echo clean done
