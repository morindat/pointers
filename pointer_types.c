#include <stdio.h>
#include <stdlib.h>

/*
 * pointer_types.c
 *
 * Covers:
 *   1. Pointer types and sizeof — why every pointer is the same size,
 *      but the TYPE it points to controls how dereferencing/arithmetic behave
 *   2. void* — the typeless pointer, and why you must cast before using it
 *   3. Reinterpreting an int's raw bytes through a char* (endianness demo)
 *   4. NULL, uninitialized, and dangling pointers — three different dangers,
 *      and what happens (or would happen) if you dereference each
 */

int main(void) {
    printf("FUN FACT...Did you know I had compiled my code with wrong order of flags, and that led to me losing the file?\n");
    /* ---------------------------------------------------------------
     * 1. Pointer types and sizeof
     * ------------------------------------------------------------- */
    int    *pi;
    double *pd;
    char   *pc;

    printf("=== 1. Pointer sizes ===\n");
    printf("sizeof(pi) [int*]    = %zu bytes\n", sizeof(pi));
    printf("sizeof(pd) [double*] = %zu bytes\n", sizeof(pd));
    printf("sizeof(pc) [char*]   = %zu bytes\n", sizeof(pc));
    /* All three print the SAME number (8 on a 64-bit system) — a pointer
     * is always just an address-sized value, regardless of what it points to.
     * What differs is the STEP SIZE used for arithmetic, and how many bytes
     * get read/written when you dereference. */

    printf("sizeof(int)    = %zu bytes  <- this is what differs, not the pointer\n", sizeof(int));
    printf("sizeof(double) = %zu bytes\n", sizeof(double));
    printf("sizeof(char)   = %zu bytes\n\n", sizeof(char));

    /* ---------------------------------------------------------------
     * 2. void* — the typeless pointer
     * ------------------------------------------------------------- */
    printf("=== 2. void* ===\n");
    int n = 42;
    void *vp = &n;
    /* *vp = 10;            // ERROR if uncommented — compiler doesn't know
     *                       // the size/type of what vp points to */
    *(int*)vp = 10;          /* must cast back to int* before dereferencing */
    printf("n via void* cast back to int* = %d\n\n", n);

    /* ---------------------------------------------------------------
     * 3. Reinterpreting an int's bytes through char* (endianness)
     * ------------------------------------------------------------- */
    printf("=== 3. Byte layout of an int (little-endian on x86-64) ===\n");
    int x = 15000;
    char *cp = (char*)&x;   /* legal — char* is special-cased to alias anything */

    printf("The value of x = %d\n", x);
    printf("First byte  of x (cp[0]) = %d\n", cp[0]);   /* low byte first */
    printf("Second byte of x (cp[1]) = %d\n", cp[1]);

    for (int i = 0; i < (int)sizeof(int); i++) {
        printf("byte %d: 0x%02hhx\n", i, cp[i]);
    }
    printf("\n");

    /* ---------------------------------------------------------------
     * 4. NULL, uninitialized, and dangling pointers
     * ------------------------------------------------------------- */
    printf("=== 4. NULL vs uninitialized vs dangling ===\n");

    /* --- NULL: deliberately points "nowhere" --- */
    int *p_null = NULL;
    printf("p_null         = %p   (explicitly points nowhere)\n", (void*)p_null);
    /* Dereferencing p_null (*p_null) would SEGFAULT immediately.
     * This is the SAFE invalid state: predictable, loud, easy to catch.
     * Left commented out on purpose — uncommenting will crash the program:
     *
     *     printf("%d\n", *p_null);
     */

    /* --- Uninitialized: contains garbage, could be ANY address --- */
    //int *p_uninit;
    //printf("p_uninit       = %p   (garbage — value is whatever was already\n", (void*)p_uninit);
    //printf("                       sitting in that stack memory)\n");
    /* Dereferencing p_uninit is UNDEFINED BEHAVIOR. It might crash, or it
     * might silently read/corrupt memory that happens to be valid-looking.
     * That unpredictability is exactly what makes it dangerous — unlike
     * NULL, it won't reliably crash to warn you something's wrong.
     *
     *     printf("%d\n", *p_uninit);   // DO NOT uncomment - undefined behavior
     */

    /* --- Dangling: pointed somewhere valid, but that memory is gone --- */
    int *p_dangling;
    {
        int local = 99;
        p_dangling = &local;
        printf("p_dangling (in scope)     = %p, *p_dangling = %d\n",
               (void*)p_dangling, *p_dangling);
    }
    /* 'local' has now gone out of scope — its stack slot is no longer
     * reserved for it. p_dangling still holds that old address, but the
     * data it once pointed to is no longer guaranteed to be there. */
    printf("p_dangling (out of scope) = %p   (DANGLING now — 'local' is gone)\n",
           (void*)p_dangling);
    /* Dereferencing it here is undefined behavior — it may still print 99
     * by coincidence (the bytes haven't been overwritten YET), or it may
     * print garbage, or crash. The danger is that it can look fine for a
     * while and then break unpredictably the moment that stack space gets
     * reused by something else.
     *
     *     printf("%d\n", *p_dangling);   // DO NOT rely on this - undefined behavior
     */

    /* --- The defensive pattern: always NULL out a pointer once its
     *     target is gone, so any future misuse crashes loudly instead
     *     of silently corrupting something. --- */
    p_dangling = NULL;
    printf("p_dangling (defensively reset to NULL) = %p\n\n", (void*)p_dangling);

    printf("=== Summary ===\n");
    printf("NULL          -> dereferencing it CRASHES immediately and loudly (safe to debug)\n");
    printf("Uninitialized -> dereferencing it is UB: might crash, might silently corrupt\n");
    printf("Dangling      -> dereferencing it is UB: may look fine for a while, then break\n");

    return 0;
}
