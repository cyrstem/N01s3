#pragma once
#include "ofMain.h"
#include "./Audio/Music.h"
#include "Button.h"
class UI {
   
    public:
//--------------------------------------------------------------    
UI(){ 
    btn.setup(50,ofGetWidth()/2,ofGetHeight()-35,ofColor::white);
    ofAddListener(btn.clickedInside, this, &UI::onMouseInButton);

    state = m._state;

    // fft = new float[256];
    //     for (int i = 0; i < 128; i++)
    //     {
    //         fft[i] =0.6;
    //     }
    
    // bands = 128;
     volume =0.7;
     
    }
//--------------------------------------------------------------
    void set(){
        // float  *val = ofSoundGetSpectrum(nBandsToGet);
        // for (int i = 0; i < nBandsToGet; i++)
        // {
        //     fftSmoothed[i] *= 0.96f;
        //     if (fftSmoothed[i] <val [i]) fftSmoothed[i] =val[i];
            
        // }
    }
   
//--------------------------------------------------------------
void onMouseInButton(ofVec2f& e){
    cout << "click in c++ yay!" << endl;

    ofFileDialogResult music = ofSystemLoadDialog("load a song");
        if (music.bSuccess)
        {   
          m.loadFile(music);
     
        }else
        {
            ofLog()<<"file not selected";
        }
}

//--------------------------------------------------------------
void show(){
//show buttons
  
   
//show spectrum analizes from song 
    // ofPushStyle();
    //    ofSetColor(ofColor::red);
    //    ofFill();
    //     float width = (float)(5*128)/nBandsToGet;
    //     for (int i = 0; i < nBandsToGet; i++)
    //     {
    //         ofDrawRectangle(65+i*width,ofGetHeight()-20,width,-(fftSmoothed[i]* 200));
    //     }
    //  ofPopStyle();



//active set up  volume 

    if (m._state ==true)
    {
        ofDrawBitmapString(ofToString(volume),ofGetWidth()-65,ofGetHeight()-20);
    }
    else
    {
        ofDrawBitmapString("volume "+ofToString(volume),ofGetWidth()-95,ofGetHeight()-20);
    }
        ofPushMatrix();
         btn.draw();
        ofPopMatrix();
}
//--------------------------------------------------------------
        //common variables
        float volume;
        bool  state;
        Button btn;
        Music m;

//visual data from sound
		// float *fft;
		// float *soundSpectrum;
		// int bands;
		// float decay ;
		// static constexpr size_t nBandsToGet = 128;
		// std::array<float,nBandsToGet> fftSmoothed{{0}}; 
       
    
};