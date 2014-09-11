CXX = /opt/bin/clang++
CFLAGS = -Iinclude $(shell pkg-config gtkmm-2.4 libunicapgtk --cflags)
CXXFLAGS = -std=c++11
LDFLAGS = $(shell pkg-config gtkmm-2.4 libunicapgtk --libs)

test: test_main
	./test_main

test_main:
	$(CXX) $(CFLAGS) $(CXXFLAGS) $(LDFLAGS) -o test_main test/main.cc src/video_window.cc src/debayer.c

.PHONY: clean
clean:
	-rm test_main
	-cd deps/libucil && make clean
	-cd deps/libunicap && make clean
	-cd deps/libunicapgtk && make clean
