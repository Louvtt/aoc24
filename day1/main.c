#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define BUF_SIZE 65536

void parse_input(const char* file, int **list1, int **list2, size_t *n) {
    FILE *f = fopen(file, "r");

    char buf[BUF_SIZE];
    size_t ln = 0;
    while(!feof(f)) {
        size_t res = fread(buf, 1, BUF_SIZE, f);
        if(ferror(f)) {
            exit(-1);
        }

        for(int i = 0; i < res; ++i) {
            if(buf[i] == '\n') ln++;
        }
    }
    *n = ln;

    *list1 = (int*)malloc(sizeof(int) * ln);
    *list2 = (int*)malloc(sizeof(int) * ln);

    fseek(f, 0, SEEK_SET);
    for(int i = 0; i < ln; ++i) {
        fscanf(f, "%d   %d\n", &(*list1)[i], &(*list2)[i]);
    }
    fclose(f);
}

int main(int argc, char **argv) {
    int *l1, *l2;
    size_t n;

    printf("Parsing file... ");
    parse_input(argv[1], &l1, &l2, &n);
    printf("done (%d lines)\n", n);

    // calculate
#ifdef PART_ONE
    int total_dist = 0;
    for(int i = 0; i < n; ++i) {
        printf("Iteration %d/%d\r", i, n);
        int smallest1 = INT_MAX;
        int smallest2 = INT_MAX;
        for(int j = i; j < n; ++j) {
            if(l1[j] < smallest1) { smallest1 = l1[j]; int tmp = l1[j]; l1[j] = l1[i]; l1[i] = tmp; }
            if(l2[j] < smallest2) { smallest2 = l2[j]; int tmp = l2[j]; l2[j] = l2[i]; l2[i] = tmp; }
        }
        total_dist += ((smallest1 < smallest2) ? (smallest2 - smallest1) : (smallest1 - smallest2));
    }
    printf("Total dist = %d\n", total_dist);
#endif

#ifdef PART_TWO
    // similarity
    int total_sim = 0;
    for(int i = 0; i < n; ++i) {
        printf("Iteration %d/%d\r", i, n);
        int sim = 0;
        for(int j = 0; j < n; ++j) {
            if(l1[i] == l2[j]) sim++;
        }
        total_sim += sim * l1[i];
    }

    printf("Similarity = %d\n", total_sim);
#endif

cleanup:
    free(l1);
    free(l2);
    return 0;
}
