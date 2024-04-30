Snake:
	clang -std=c++14 -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/libraylib.a Snake.cpp -o Snake 
clean:
	rm Snake
