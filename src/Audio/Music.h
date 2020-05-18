#pragma once
#include "ofMain.h"

class Music {
    public:
    //methots or functions 

    Music(){
        ofLog()<<"music coder loaded";
        _state= false;
        fft = new float[256];
        for (int i = 0; i < 128; i++)
        {
            fft[i] =0.6;
        }
    
        bands = 128;
    }
    void setAudio();
    void loadFile(ofFileDialogResult data);
    void utilDraw();
  

    ofSoundPlayer song;
    bool _state;
    float volume;

    //visual data from sound
		float *fft;
		float *soundSpectrum;
		int bands;
		float decay ;
		static constexpr size_t nBandsToGet = 128;
		std::array<float,nBandsToGet> fftSmoothed{{0}}; 
};