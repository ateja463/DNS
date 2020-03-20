
all : server client

server :main.o
	$(CXX) main.o -o server -pthread

client:client.o
	$(CXX) client.o -o client

main.o:AVLTree.cpp AVLTree.h main.cpp
	$(CXX) -c main.cpp

client.o:client.cpp
	$(CXX) -c client.cpp

	

