#pragma once
#include "ofMain.h"

class Music {
    public:
    ofSoundPlayer song;
    bool _state;
    float volume;
    float *fft;
    float *ofSoundGetSpectrum;
    int bands;
    float decay;
     


    //methots or functions 

        Music(){
            ofLog()<<"music coder loaded";
            _state= false;
        }
    //void volume(float &volume);
    void loadFile(ofFileDialogResult data);

    



};