#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>
#include <limits.h>

//--------------------------------Global variables starts---------------------------------
int verbose = 0;
int s = -1; // Number of set index bits
int E = -1; // Associativity (number of lines per set
int b = -1; // Number of block bits (B = 2^b is the block size)
char *tracefile = NULL;

int hits = 0;
int misses = 0;
int evictions = 0;

int my_clock = 0;

typedef struct {
    int valid; // 1 valid bit per line
    unsigned long tag; // 64 - s - b tag bits per line
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
            cache[i][j].tag = -1;
            cache[i][j].time_stamp = 0;
        }
    }
    return;
}

/*
cache access operation(L or S), access some bytes from address.

Return a 2-bit number where the 0-th bit indicates cache hit/miss
1st bit represents evictions.

Below are possible return values:
0: cache miss, no eviction
1: cache hit,  no eviction
2: cache miss, eviction
3: cache hit,  eviction

If cache hit, do hits++, otherwise misses++.
If eviction, evictions++.

At the end of function, print something based on verbose.
*/
int cache_access(unsigned long address, int bytes, int verbose, int l){
    // TODO
    // Compute the set of the address
    unsigned long set = address >> b & ((1 << s) - 1);

    // Compute the tag
    unsigned long tag = address >> (b + s);

    // Go to the corresponding cache set
    cache_line *cache_set = cache[set];

    // Search each line in the set for the data, do below 4 tasks in one search
    // 1. Whether it has data(hit)
    // 2. Whether there is a free cache line(has_free_line), if yes, record the index
    // 3. The index of the valid LRU cache line, i.e., the line with min time stamp(invalid_line_index)
    int hit = 0; // cache hit or cache miss
    int has_free_line = 0;
    int free_line_index = -1;

    int lru_time = INT_MAX; // timestamp of lru cache line
    int lru_index = -1; // index of the lru cache line

    
    for(int i = 0; i < E; i++){
        cache_line line = cache_set[i];

        // cache hit
        if(line.valid == 1 && line.tag == tag){
            hit = 1;
            // update hits
            hits++;
            (cache_set + i)->time_stamp = my_clock;
            break;
        }

        // search for free line
        if(has_free_line == 0 && line.valid == 0){
            free_line_index = i;
            has_free_line = 1;
        }

        // search the lru cache line
        if(line.valid == 1 && line.time_stamp < lru_time){
            lru_time = line.time_stamp;
            lru_index = i;
        }
    }

    // cache miss
    int eviction = 0;
    if(hit == 0){
        // update misses
        misses++;

        // if there is free line, perfect, just write to that line!
        if(has_free_line){
            cache_set[free_line_index].valid = 1;
            cache_set[free_line_index].tag = tag;
            cache_set[free_line_index].time_stamp = my_clock;
        }

        // if there is no free line, ooops, need to evict a line
        else{
            // update evictions
            evictions++;
            eviction = 1;
            
            cache_set[lru_index].tag = tag;
            cache_set[lru_index].time_stamp = my_clock;
        }
    }


    if(verbose){
        if(l)
            printf("L %lx,%d", address, bytes);
        else
            printf("S %lx,%d", address, bytes);

        if(hit)
            printf(" hit");
        else
            printf(" miss");

        if(eviction)
            printf(" eviction");

        printf("\n");
    }
    return (eviction << 1) | hit;
}


/*
M operation, modify some bytes in address, i.e., 
a load followed by a store. M = L S

At the end of function, print something based on verbose.
*/
void M(unsigned long address, int bytes, int verbose){
    int l = cache_access(address, bytes, 0, 1);
    my_clock++;
    hits++;

    int l_hit = l & 1;
    int l_eviction = (l & 2) >> 1;

    if(verbose){
        printf("M %lx,%d", address, bytes);

        if(l_hit)
            printf(" hit");
        else
            printf(" miss");

        if(l_eviction)
            printf(" eviction");

        // Second access must be a hit
        printf(" hit\n");
    }
    return;
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
        //printf("Operation: %c address: %lx size: %d\n", operation, address, size);
        my_clock++;
        switch (operation)
        {
        case 'L':
            //printf("L\n");
            cache_access(address, size, verbose, 1);
            break;
        case 'M':
            //printf("M\n");
            M(address, size, verbose);
            break;
        case 'S':
            //printf("S\n");
            cache_access(address, size, verbose, 0);
            break;
        default:
            continue;
        }
    }
    return;
}

int main(int argc, char *argv[])
{
    int opt;
    // parse the command line argument and set global variables
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
