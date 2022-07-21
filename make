project : main.o preAssembler.o firstStep.o secondStep.o thirdStep.o convert.o label.o orders.o
    gcc -Wall -ansi -pedantic main.o preAssembler.o firstStep.o secondStep.o thirdStep.o convert.o label.o orders.o -o main_project
main.o : main.c assembler.h
    gcc -c -Wall -ansi -pedantic main.c
preAssembler.o : preAssembler.c assembler.h
    gcc -c -Wall -ansi -pedantic preAssembler.c
firstStep.o : firstStep.c assembler.h
    gcc -c -Wall -ansi -pedantic firstStep.c
secondStep.o : secondStep.c assembler.h
    gcc -c -Wall -ansi -pedantic secondStep.c
thirdStep.o : thirdStep.c assembler.h
    gcc -c -Wall -ansi -pedantic thirdStep.c
convert.o : convert.c assembler.h
    gcc -c -Wall -ansi -pedantic convert.c
label.o : label.c assembler.h
    gcc -c -Wall -ansi -pedantic label.c
orders.o : orders.c assembler.h
    gcc -c -Wall -ansi -pedantic orders.c
