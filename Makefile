CXX = g++
CXXFLAGS = -g -Wall -Werror
EXECS = rpg
ITEMS = items/item.o items/armor.o items/weapon.o items/skill.o
ENTITIES = entities/entity.o entities/player.o
STRUCTURES = structures/dungeon.o structures/shop.o

all: $(EXECS)
rpg: main.o $(ENTITIES) $(ITEMS) $(STRUCTURES)
	$(CXX) $(CXXFLAGS) -o $@ $^
clean:
	rm -f *.o $(EXECS)
	cd entities && rm -f *.o
	cd items && rm -f *.o
	cd structures && rm -f *.o