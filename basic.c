#include <stdio.h>


int main() {
	// Pointer: A pointer is nothing but a variable whose value is one of the adresses allocated to the program
	// Even more directly a pointer is a variable that stores a memory address of another variable, rather than holding data directly
	
	int x = 42;  // x is a variable that stores the value 42
	int *p = &x; // p is a pointer of type int that stores the memory address of x

	// Core operators
	// & -> address of: Give me the address where "that variable" lives
	// * -> dereference: Go to the address stored here, and give me what is in there
	
	printf("x = %d\n", x);	
	printf("Address: %p\n", p);
	
	// Also we can use the address to get the value and use & to get address directly without using p
	printf("x = %d\n", *p);
	printf("Address: %p\n", &x);
	
	// You can also use the address directly to change the value of x
	*p = 100;
	printf("now x = %d\n", x);
	// And the address should assumably stay the same, just try it out for demonstration purposes
	printf("address should stay the same: %p\n", p);

	// Though for most compiler it is not an issue, printf %p require an argument of type void* so we mostly do include it	
	printf("address should stay the same: %p\n", (void *)p);
	
	return 0;
}
