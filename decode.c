#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define BILLION  1000000000.0;


int main(void) {
    struct timespec start, end;
    if (getenv("SPEECH_RECOGNITION") == NULL) {
	system("echo Please set the SPEECH_RECOGNITION environment variable to point to the git repository");
	return 1;
    }
    system("export LD_LIBRARY_PATH=/usr/local/lib");
    system("aplay $SPEECH_RECOGNITION/beep-07.wav");
    system("arecord --format=S16_LE --duration=5 -r 16000 --file-type=wav inputs/noisy.wav");
    system("aplay $SPEECH_RECOGNITION/beep-08b.wav");
    system("echo done recording...");
    system("python noiseClean.py");
    system("echo done cleaning...");
    clock_gettime(CLOCK_REALTIME, &start);
    system("\
        pocketsphinx_continuous \
        -infile inputs/filtered.wav \
        -dict ./models/corpus/Corpus_V3/100.dic \
        -lm ./models/corpus/Corpus_V3/100.lm \
        2>./output/unwanted-stuff.log | tee ./output/words.txt");
    // pocketsphinx_continuous -infile testfiles/speech.wav -dict dicts/8050.dic -lm dicts/8050.lm 2>./output/unwanted-stuff.log | tee ./output/words.txt
    system("echo done decoding...");
    clock_gettime(CLOCK_REALTIME, &end);
    double time_spent = (end.tv_sec - start.tv_sec) +
						(end.tv_nsec - start.tv_nsec) / BILLION;
    char *timerOutput = malloc(25);
    sprintf(timerOutput, "echo Time Elapsed: %f\n", time_spent);
    system(timerOutput);
}
