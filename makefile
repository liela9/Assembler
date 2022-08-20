project : main.o preAssembler.o firstPass.o secondPass.o macro.o conversionUtils.o lists.o lines.o writeFiles.o utils.o 
	gcc -g -Wall -ansi -pedantic main.o preAssembler.o firstPass.o secondPass.o macro.o conversionUtils.o lists.o lines.o writeFiles.o utils.o -o project -lm

main.o : main.c constants.h
	gcc -g -Wall -ansi -pedantic -c main.c -o main.o

preAssembler.o : preAssembler.c constants.h preAssembler.h
	gcc -g -Wall -ansi -pedantic -c preAssembler.c -o preAssembler.o

firstPass.o : firstPass.c constants.h firstPass.h
	gcc -g -Wall -ansi -pedantic -c firstPass.c -o firstPass.o

secondPass.o : secondPass.c constants.h secondPass.h
	gcc -g -Wall -ansi -pedantic -c secondPass.c -o secondPass.o

macro.o : macro.c constants.h macro.h
	gcc -g -Wall -ansi -pedantic -c macro.c -o macro.o

conversionUtils.o : conversionUtils.c constants.h conversionUtils.h
	gcc -g -Wall -ansi -pedantic -c conversionUtils.c -o conversionUtils.o

lists.o : lists.c constants.h lists.h
	gcc -g -Wall -ansi -pedantic -c lists.c -o lists.o

lines.o : lines.c constants.h lines.h
	gcc -g -Wall -ansi -pedantic -c lines.c -o lines.o

writeFiles.o : writeFiles.c constants.h writeFiles.h
	gcc -g -Wall -ansi -pedantic -c writeFiles.c -o writeFiles.o

utils.o : utils.c constants.h utils.h
	gcc -g -Wall -ansi -pedantic -c utils.c -o utils.o

