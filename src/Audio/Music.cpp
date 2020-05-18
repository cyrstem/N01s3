#include "Music.h"
void Music::setAudio(){
      float  *val = ofSoundGetSpectrum(nBandsToGet);
        for (int i = 0; i < nBandsToGet; i++)
        {
            fftSmoothed[i] *= 0.96f;
            if (fftSmoothed[i] <val [i]) fftSmoothed[i] =val[i];
            
        }
}
//--------------------------------------------------------------
    void Music::loadFile(ofFileDialogResult data){
        ofFile file (data.getPath());
    
        if(file.exists()){
            song.unloadSound();
            ofLog()<<file.getAbsolutePath();
            song.load(file);
        }
        if(song.isLoaded()){
        _state = true;
            song.play();
        }
        else{
            ofLog()<<"at least load a file ";
        _state = false;
        }
    }
//--------------------------------------------------------------
void Music::utilDraw(){
           
//show spectrum analizes from song 
    ofPushStyle();
       ofSetColor(ofColor::red);
       ofFill();
        float width = (float)(5*128)/nBandsToGet;
        for (int i = 0; i < nBandsToGet; i++)
        {
            ofDrawRectangle(65+i*width,ofGetHeight()/2,width,-(fftSmoothed[i]* 200));
        }
     ofPopStyle();



    }

