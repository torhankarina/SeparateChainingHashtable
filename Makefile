CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

hash: hashmain.o htable.o
	$(CXX) $(CXXFLAGS) -o hash hashmain.o htable.o

hashmain.o: hashmain.cc hashmain.h htable.h entry.h
	$(CXX) $(CXXFLAGS) -c hashmain.cc

htable.o: htable.cc htable.h entry.h
	$(CXX) $(CXXFLAGS) -c htable.cc

clean:
	rm -f hash hashmain.o htable.o

.PHONY: clean