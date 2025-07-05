all: report.exe

report.exe: report.o temp_function.o
	gcc -o report.exe report.o temp_function.o

report.o: report.c temp_function.h
	gcc -c -o report.o report.c

temp_function.o: temp_function.c temp_function.h
	gcc -c -o temp_function.o temp_function.c

clean: 
	del  *.o  *.exe