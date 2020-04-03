#include "Music.h"

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
    // void Music::volume(float &volume){

    // }
//--------------------------------------------------------------