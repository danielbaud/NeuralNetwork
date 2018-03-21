CXX = g++
CXXFLAGS = -Werror -Wextra -Wall -pedantic -std=c++17 -g

TRASH = run create plotn

all: run

.PHONY: run
run:
	$(CXX) $(CXXFLAGS) -o run src/run_network.cc

.PHONY: create
create:
	$(CXX) $(CXXFLAGS) -o create src/create_network.cc

.PHONY: plot
plot:
	$(CXX) $(CXXFLAGS) -o plotn plot/plot.cc

.PHONY: clean
clean:
	$(RM) $(TRASH)

.PHONY: install
install:
	make -s create
	make -s run
	make -s plot
	sudo mv create /bin/anncreate
	sudo mv run /bin/annrun
	sudo mv plotn /bin/annplot
	make -s clean
