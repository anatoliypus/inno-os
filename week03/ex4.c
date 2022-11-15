#include <stdio.h>
#include <stdlib.h>

void* addInt(const void* a, const void* b){
    if (sizeof(*a) == sizeof(int) && sizeof(*b) == sizeof(int)) {
        int * result = malloc(sizeof(int));
        *result = *((const int*) a) + *((const int*) b);
        return result;
    }
    return NULL;
}

void* aggregate(void* base, size_t size, int n, void* initial_value, void* (*opr)(const void*, const void*)){

	void* output;

	if (size==sizeof(int)){ // base is a pointer to an integer
	
        return aggregate(base + 1, size, n - 1, opr(initial_value, base), opr);


	} else { // base is a pointer to a double
	    return aggregate(base + 1, size, n - 1, opr(initial_value, base), opr);
	}

	return output;
}




int main(){

        int ints[] = {1, 2, 3, 4, 5};
        double doubles = {1.5, 2.5, 3.5, 4.5, 5.5};
	
        int* result1a = aggregate(ints, sizeof(int), 5, 0, addInt);        
        printf("%d\n", *result1a);

        return EXIT_SUCCESS;
}
