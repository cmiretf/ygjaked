#MACROS
GC=gcc
FLAGS= -g -Wall -ansi -pedantic

#EJECUTABLES 
exe: space.o screen.o graphic_engine.o game_loop.o game.o command.o game_reader.o object.o player.o set.o die.o
	$(GC) $(FLAGS) -o exe space.o screen.o graphic_engine.o game_loop.o game.o command.o game_reader.o object.o player.o set.o die.o

#TESTS
set_test: set.o set_test.o
	$(GC) $(FLAGS) -o set_test set.o set_test.o
die_test: die.o die_test.o
	$(GC) $(FLAGS) -o die_test die.o die_test.o


#OBJETOS
player.o: player.c player.h
	$(GC) $(FLAGS) -c player.c

object.o:object.c object.h types.h
	$(GC) $(FLAGS) -c object.c

game_reader.o:game_reader.c game_reader.h types.h
	$(GC) $(FLAGS) -c game_reader.c

space.o: space.c space.h types.h object.h set.h player.h
	$(GC) $(FLAGS) -c space.c

screen.o: screen.c screen.h
	$(GC) $(FLAGS) -c screen.c

graphic_engine.o: graphic_engine.c screen.h graphic_engine.h
	$(GC) $(FLAGS) -c graphic_engine.c

game_loop.o: game_loop.c graphic_engine.h
	$(GC) $(FLAGS) -c game_loop.c

game.o: game.c game.h player.h object.h command.h space.h die.h game_reader.h types.h
	$(GC) $(FLAGS) -c game.c

command.o: command.c command.h
	$(GC) $(FLAGS) -c command.c

set.o: set.c set.h types.h
	$(GC) $(FLAGS) -c set.c

set_test.o: set.h set_test.c types.h
	$(GC) $(FLAGS) -c set_test.c
vset:
	valgrind --leak-check=full ./set_test

die.o: die.c die.h types.h
	$(GC) $(FLAGS) -c die.c

die_test.o: die.h die_test.c  types.h
	$(GC) $(FLAGS) -c die_test.c
vdie:
	valgrind --leak-check=full ./die_test

clean:
	rm -f *.o
	rm -f exe
	rm -f set_test
	rm -f die_test
	rm -f *.tar.gz
val:
	valgrind --leak-check=full ./exe data.dat

comprimir:
	tar -czvf I2_PAREJA5_G2161_PPROG.tar.gz *.h *.c data.dat makefile
