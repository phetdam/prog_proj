/**
 * daqh.c
 *
 * solution to the hackerrank problem "Dynamic Array", where one is tasked with
 * creating n dynamic arrays, and handling two types of queries on these arrays.
 * the first query will append an integer y to the dynamic array at [zero-indexed]
 * index (x ^ k) % n, where k is an integer that is updated by the second query.
 * the second query updates k by finding the dynamic array at index (x ^ k) % n,
 * finding the element at index y % s where s is the size of that dynamic array,
 * and then updating k with that value. 
 *
 * it is guaranteed that query type 1 will always be called before query type 2,
 * and that query type 2 will never ask for a dynamic array of size 0. input file
 * dynamic_array_input06 is included as an input file to be read in from stdin.
 *
 * recommended compilation is 'gcc -Wall -g -o daqh daqh.c'. please run by reading
 * the input file from stdin: './daqh < dynamic_array_input06'
 *
 * Changelog:
 *
 * 09-18-2018
 *
 * initial commit to C source file from HackerRank online buffer. modified to 
 * write to local file daqh_out, and added change log.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// program name "dynamic array query handler"
#define PROGNAME "daqh"
// default size of dynamic array at beginning
#define AUTO_SIZ 10
// default name of output file (not included in hackerrank original version)
#define OUT_FILE "daqh_out"

// struct for dynamic int array; we need to keep track of the max and current size
struct d_int {
    // pointer to integer [array], current size of a, max size of a
    int *a, siz, max_siz;
};
typedef struct d_int d_int;
// creates a new d_int; if AUTO_SIZ is given then starting size is 10 by default
d_int *new_d_int(int n) {
    assert(n > 0);
    // create new d_int struct
    d_int *di = (d_int *) malloc(sizeof(d_int));
    // new int array size n, current size 0, max size n
    di->a = (int *) malloc(n * sizeof(int));
    di->siz = 0;
    di->max_siz = n;
    return di;
}
// frees a d_int struct
void free_d_int(d_int *di) {
    free(di->a);
    free(di);
}
// appends an item to the int array of the d_int struct, resizing as needed
void append(d_int *di, int k) {
    // if the array is full, double its size
    if (di->siz == di->max_siz) {
        di->max_siz *= 2;
        di->a = (int *) realloc(di->a, di->max_siz * sizeof(int));
        if (di->a == NULL) { 
            fprintf(stderr, "%s: realloc failure\n", PROGNAME);
            exit(2);
        }
    }
    // append k to the array
    *(di->a + (di->siz)++) = k;
}
// struct for query; no constructor because we will manually construct this
struct qry {
    // query type, x and y
    int tp, x, y;
};
typedef struct qry qry;

// handles qry struct for the given d_int **, where there are n d_int *; *lv points
// to the "last answer" integer which will be modified only with queries of type 2
void dynamic_query_handler(d_int **mat, int n, qry *q, int *lv) {
    assert(n > 0);
    // calculate index of d_int
    int i = (q->x ^ *lv) % n;
    // if the query is of type 1
    if (q->tp == 1) {
        // append q->y to d_int * *(mat + i)
        append(*(mat + i), q->y);
    }
    // else if the query of type 2
    else if (q->tp == 2) {
        // get an index in the int array in d_int * *(mat + i)
        int j = q->y % (*(mat + i))->siz;
        // assign the value to lv
        *lv = *((*(mat + i))->a + j);
    }
    // else print error and exit
    else {
        fprintf(stderr, "%s: unrecognized query type\n", PROGNAME);
        exit(3);
    }
}

int main(int argc, char **argv)
{
    // output file
    FILE *f = fopen(OUT_FILE, "w");
    // number of dynamic arrays to maintain, number of queries to process, loop index,
    // "last answer" integer value
    int a_n, q_n, i, lv;
    scanf("%d %d", &a_n, &q_n);
    // malloc array of d_int * and individual d_int *
    d_int **mat = (d_int **) malloc(a_n * sizeof(d_int *));
    lv = i = 0;
    while (i < a_n) {
        *(mat + i++) = new_d_int(AUTO_SIZ);
    }
    // process all queries
    i = -1;
    while (++i < q_n) {
        // new query
        qry *q = (qry *) malloc(sizeof(qry));
        // read in relevant values
        scanf("%d %d %d", &q->tp, &q->x, &q->y);
        // handle query (lv will be updated as appropriate)
        dynamic_query_handler(mat, a_n, q, &lv);
        // if the query was a type 2 query, write lv to file
        if (q->tp == 2) { fprintf(f, "%d\n", lv); }
        // free query
        free(q);
    }
    fclose(f);
    // free all used memory
    i = 0;
    while (i < a_n) {
	free_d_int(*(mat + i++));
    }
    free(mat);
    return 0;
}
