#project2.2 makefile
SRCS 		:= subway_portal.cpp subway_station.cpp subway_system.cpp _hash_item.cpp hash_table.cpp gps.cpp
OBJS 		:= $(patsubst %.cpp, %.o, $(SRCS)) main.o subway_route.o
EXEC 		:= main
CXX 		:= g++
CXXFLAGS	:= $(CXXFLAGS) -Wall -std=c++11 -g

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

clean:
	$(RM) $(EXEC) subway_portal.o subway_station.o subway_system.o gps.o _hash_item.o hash_table.o
