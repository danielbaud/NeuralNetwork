CXX = g++
CXXFLAGS = -Werror -Wextra -Wall -pedantic -std=c++17

TRASH = run create

all: run

.PHONY: run
run:
	$(CXX) $(CXXFLAGS) -o run src/run_network.cc

.PHONY: create
create:
	$(CXX) $(CXXFLAGS) -o create src/create_network.cc

.PHONY: clean
clean:
	$(RM) $(TRASH)
