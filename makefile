project : main.o preAssembler.o firstStep.o secondStep.o macro.o converting.o lists.o lines.o writeFiles.o utils.o 
	gcc -g -Wall -ansi -pedantic main.o preAssembler.o firstStep.o secondStep.o macro.o converting.o lists.o lines.o writeFiles.o utils.o -o project -lm

main.o : main.c constants.h
	gcc -g -Wall -ansi -pedantic -c main.c -o main.o

preAssembler.o : preAssembler.c constants.h preAssembler.h
	gcc -g -Wall -ansi -pedantic -c preAssembler.c -o preAssembler.o

firstStep.o : firstStep.c constants.h firstStep.h
	gcc -g -Wall -ansi -pedantic -c firstStep.c -o firstStep.o

secondStep.o : secondStep.c constants.h secondStep.h
	gcc -g -Wall -ansi -pedantic -c secondStep.c -o secondStep.o

macro.o : macro.c constants.h macro.h
	gcc -g -Wall -ansi -pedantic -c macro.c -o macro.o

converting.o : converting.c constants.h converting.h
	gcc -g -Wall -ansi -pedantic -c converting.c -o converting.o

lists.o : lists.c constants.h lists.h
	gcc -g -Wall -ansi -pedantic -c lists.c -o lists.o

lines.o : lines.c constants.h lines.h
	gcc -g -Wall -ansi -pedantic -c lines.c -o lines.o

writeFiles.o : writeFiles.c constants.h writeFiles.h
	gcc -g -Wall -ansi -pedantic -c writeFiles.c -o writeFiles.o

utils.o : utils.c constants.h utils.h
	gcc -g -Wall -ansi -pedantic -c utils.c -o utils.o

