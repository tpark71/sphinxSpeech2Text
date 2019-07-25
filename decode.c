#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define BILLION  1000000000.0;


int main(void) {
    struct timespec start, end;

    system("export LD_LIBRARY_PATH=/usr/local/lib");
    system("arecord --format=S16_LE --duration=5 --rate=16k -D sysdefault:CARD=1 --file-type=wav testfiles/noisy.wav");
    system("echo done recording...");
    system("python testfiles/noiseClean.py");
    system("echo done cleaning...");
    clock_gettime(CLOCK_REALTIME, &start);
    system("\
        pocketsphinx_continuous \
        -infile testfiles/filtered.wav \
        -dict dicts/8050.dic \
        -lm dicts/8050.lm \
        2>./output/unwanted-stuff.log | tee ./output/words.txt");
    // pocketsphinx_continuous -infile testfiles/Untitled.wav -dict dicts/8050.dic -lm dicts/8050.lm 2>./output/unwanted-stuff.log | tee ./output/words.txt
    system("echo done decoding...");
    clock_gettime(CLOCK_REALTIME, &end);
    double time_spent = (end.tv_sec - start.tv_sec) +
						(end.tv_nsec - start.tv_nsec) / BILLION;
    char *timerOutput = malloc(25);
    sprintf(timerOutput, "echo Time Elapsed: %f\n", time_spent);
    system(timerOutput);
}