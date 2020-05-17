
all: out
	echo build done

out: render.o
	g++ -o out render.o

render.o: render.cpp
	g++ -c render.cpp

clean:
	rm render.o out
	echo clean done
