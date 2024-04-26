run: div_bug
	./div_bug

div_bug: div_bug.c
	clang -masm=intel -o div_bug div_bug.c
   
clean:
	rm -f *.o div_bug
