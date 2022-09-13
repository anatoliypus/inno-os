#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    int int_v = __INT_MAX__;
    unsigned short int unsigned_short_int_v = USHRT_MAX;
    signed long int signed_long_int_v = LONG_MAX;
    float float_v = FLT_MAX;
    double double_v = DBL_MAX;
    
    printf("Type: Unsigned short int\n");
    printf("Size: %lu\n", sizeof(unsigned_short_int_v));
    printf("Max value: %d\n\n", unsigned_short_int_v);

    printf("Type: Signed long int\n");
    printf("Size: %lu\n", sizeof(signed_long_int_v));
    printf("Max value: %ld\n\n", signed_long_int_v);

    printf("Type: Float\n");
    printf("Size: %lu\n", sizeof(float_v));
    printf("Max value: %f\n\n", float_v);

    printf("Type: Double\n");
    printf("Size: %lu\n", sizeof(double_v));
    printf("Max value: %f\n\n", double_v);
    return 0;
}
