project : main.o preAssembler.o firstStep.o secondStep.o macro.o converting.o label.o lines.o writeFiles.o utils.o free.o
	gcc -g -Wall -ansi -pedantic main.o preAssembler.o firstStep.o secondStep.o macro.o converting.o label.o lines.o writeFiles.o utils.o free.o -o project

main.o : main.c constants.h
	gcc -g -Wall -ansi -pedantic -c main.c -o main.o

preAssembler.o : preAssembler.c constants.h preAssembler.h
	gcc -g -Wall -ansi -pedantic -c preAssembler.c -o preAssembler.o

firstStep.o : firstStep.c constants.h firstStep.h
	gcc -Wall -ansi -pedantic -c firstStep.c -o firstStep.o

secondStep.o : secondStep.c constants.h secondStep.h
	gcc -g -Wall -ansi -pedantic -c secondStep.c -o secondStep.o

macro.o : macro.c constants.h macro.h
	gcc -g -Wall -ansi -pedantic -c macro.c -o macro.o

converting.o : converting.c constants.h converting.h
	gcc -g -Wall -ansi -pedantic -c converting.c -o converting.o

label.o : label.c constants.h label.h
	gcc -g -Wall -ansi -pedantic -c label.c -o label.o

lines.o : lines.c constants.h lines.h
	gcc -g -Wall -ansi -pedantic -c lines.c -o lines.o

writeFiles.o : writeFiles.c constants.h writeFiles.h
	gcc -g -Wall -ansi -pedantic -c writeFiles.c -o writeFiles.o

utils.o : utils.c constants.h utils.h
	gcc -g -Wall -ansi -pedantic -c utils.c -o utils.o

free.o : free.c constants.h free.h
	gcc -g -Wall -ansi -pedantic -c free.c -o free.o

