#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

//--------------------------------Global variables starts---------------------------------
int verbose = 0;
int s = -1;
int E = -1;
int b = -1;
char *tracefile = NULL;

int hits = 0;
int misses = 0;
int evictions = 0;

typedef struct {
    int valid; // 1 valid bit per line
    int tag; // 64 - s - b tag bits per line
    int time_stamp; // the last time this cache line was used
} cache_line;


cache_line **cache;
//--------------------------------Global variables ends-----------------------------------


void print_ussage(){
    printf("Usage: ./csim [-hv] -s <num> -E <num> -b <num> -t <tracefile>\n");
    printf("Options:\n");
    printf("  -h: Optional help flag that prints usage info\n");
    printf("  -v: Optional verbose flag that displays trace info\n");
    printf("  -s <s>: Number of set index bits (S = 2^s is the number of sets)\n");
    printf("  -E <E>: Associativity (number of lines per set)\n");
    printf("  -b <b>: Number of block bits (B = 2^b is the block size)\n");
    printf("  -t <tracefile>: Name of the valgrind trace to replay\n\n");
}

void print_param(){
    printf("v: %d \n", verbose);
    printf("s: %d \n", s);
    printf("E: %d \n", E);
    printf("b: %d \n", b);
    printf("tracefile: %s \n", tracefile);
}

/*
Initialize the cache based on the received params.

typedef struct {
    int valid; // 1 valid bit per line
    int tag; // 64 - s - b tag bits per line
    int time_stamp; // the last time this cache line was used
} cache_line;

cache_line **cache;
*/
void initialize_cache(){
    // total number of sets
    int set_num = 1 << s;
    cache = (cache_line **) malloc(set_num * sizeof(cache_line *));

    // update E cache lines for each set, there are set_num sets in total
    for(int i = 0; i < set_num; i++) {
        cache[i] = (cache_line *) malloc(E * sizeof(cache_line));
        // set the valid bit, tag bits and data in each cache line to 0
        for(int j = 0; j < E; j++){
            cache[i][j].valid = 0;
            cache[i][j].tag = 0;
            cache[i][j].time_stamp = 0;
        }
    }
    return;
}

/*
L operation, read some bytes from address.

Return 1 if cache hit, 0 if cache miss.
*/
int L(int address, unsigned long bytes){
    // TODO
    return 0;
}

/*
M operation, modify some bytes in address

Return 1 if cache hit, 0 if cache miss.
*/
int M(int address, unsigned long bytes){
    // TODO
    return 0;
}

/*
S operation, store some bytes to address

Return 1 if cache hit, 0 if cache miss.
*/
int S(int address, unsigned long bytes){
    // TODO
    return 0;
}

/*
Parse the trace files and call the corresponding
functions. Simple to implement
*/
void parse_trace(char *filename){
    char operation;
    unsigned long address;
    int size;

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, " %c %lx,%d", &operation, &address, &size) > 0){
        switch (operation)
        {
        case 'L':
            if(L(address, size) == 0){
                misses++; 
            }else
                hits++;          
            break;
        case 'M':
            if(M(address, size) == 0){
                misses++; 
            }else
                hits++;  
            break;
        case 'S':
            if(S(address, size) == 0){
                misses++; 
            }else
                hits++;  
            break;
        default:
            printf("Invalid operation!\n");
            return;
        }
    }
    return;
}

int main(int argc, char *argv[])
{
    int opt;
    while ((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1) {
    switch (opt) {
        case 'h':
            print_ussage();
            break;
        case 'v':
            verbose = 1;
            break;
        case 's':
            s = atoi(optarg);
            break;
        case 'E':
            E = atoi(optarg);
            break;
        case 'b':
            b = atoi(optarg);
            break;
        case 't':
            tracefile = optarg;
            break;
        default:
            print_ussage();
            break;
        }
    }

    // Check parameters
    if(s < 0 || E < 0 || b < 0 || tracefile == NULL){
        printf("Wrong parameter!\n\n");
        print_ussage();
        exit(0);
    }

    // Print out parameters
    print_param();

    // Initialize the cache
    initialize_cache();

    // Then, parse the trace file
    parse_trace(tracefile);

    // Finally, parse the trace files
    printSummary(hits, misses, evictions);
}
