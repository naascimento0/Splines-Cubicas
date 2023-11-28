run: 
	gcc -o exec main.c source/*.c -lm
	./exec
	
clean:
	rm -r exec
	rm -r grafico.txt
	
entrada:
	gcc -o exec main.c source/*.c -lm
	./exec < entrada.txt
	
valgrind:
	gcc -o exec main.c source/*.c -lm
	valgrind ./exec < entrada.txt
