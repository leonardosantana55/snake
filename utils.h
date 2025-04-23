#ifndef UTILS
#define UTILS


typedef struct Fps_{
    
    Uint32 time_start;
    Uint32 time_end;
    Uint32 elapsed;
    Uint32 timer;
    Uint32 frames;
    double fps;
    Uint32 desired_fps;
    int surplus;
} Fps;


Fps* Fps_Init();

void Fps_Measure(Fps *fps);

int randomIntGen(int min, int max);


#endif
