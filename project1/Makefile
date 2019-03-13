# A Sample Makefile

SRCS       := tree.cpp tree_collection.cpp AvlTree.cpp  tree_species.cpp
OBJS       := $(patsubst %.cpp, %.o, $(SRCS))  main.o
OBJSB	   := $(patsubst %.cpp, %.o, $(SRCS)) #dont clean main.o
EXEC       := project1 
CXX        := /usr/bin/g++
CXXFLAGS     += -Wall -g

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS)  -o $@  $(OBJS)

.PHONY: clean cleanall
cleanall: clean
	$(RM) $(EXEC)

clean:
	$(RM) $(OBJSB)

tree_species.h:    __tree_species.h
tree_collection.h: __tree_collection.h
avl.o:             AvlTree.h tree.h utilities.h
tree_collection.o: tree.h tree_species.h
tree.o:            tree.h 
tree_species.o:    tree_species.h
