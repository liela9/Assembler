project : main.o preAssembler.o firstStep.o secondStep.o macro.o converting.o label.o lines.o constants.o writeFiles.o utils.o free.o
    gcc -Wall -ansi -pedantic main.o preAssembler.o firstStep.o secondStep.o macro.o converting.o label.o lines.o constants.o writeFiles.o utils.o free.o -o main_project
main.o : main.c assembler.h
    gcc -c -Wall -ansi -pedantic main.c
preAssembler.o : preAssembler.c 
    gcc -c -Wall -ansi -pedantic preAssembler.c
firstStep.o : firstStep.c 
    gcc -c -Wall -ansi -pedantic firstStep.c
secondStep.o : secondStep.c 
    gcc -c -Wall -ansi -pedantic secondStep.c
macro.o : macro.c 
    gcc -c -Wall -ansi -pedantic macro.c
converting.o : converting.c 
    gcc -c -Wall -ansi -pedantic convert.c
label.o : label.c 
    gcc -c -Wall -ansi -pedantic label.c
lines.o : lines.c 
    gcc -c -Wall -ansi -pedantic lines.c
constants.o : constants.c 
    gcc -c -Wall -ansi -pedantic constants.c
writeFiles.o : writeFiles.c 
    gcc -c -Wall -ansi -pedantic writeFiles.c
utils.o : utils.c 
    gcc -c -Wall -ansi -pedantic utils.c
free.o : free.c 
    gcc -c -Wall -ansi -pedantic free.c