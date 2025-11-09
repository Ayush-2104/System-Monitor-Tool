CXX = g++
CXXFLAGS = -Wall -std=c++17

OBJS = main.o monitor.o ui.o utils.o

all: system_monitor

system_monitor: $(OBJS)
	$(CXX) $(CXXFLAGS) -o system_monitor $(OBJS)

main.o: main.cpp monitor.h ui.h
monitor.o: monitor.cpp monitor.h utils.h
ui.o: ui.cpp ui.h monitor.h
utils.o: utils.cpp utils.h

clean:
	rm -f *.o system_monitor
