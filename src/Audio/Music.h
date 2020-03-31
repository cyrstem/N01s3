#pragma once
#include "ofMain.h"

class Music {
    public:
    ofSoundPlayer song;
    bool _state;


    //methots or functions 

        Music(){
            ofLog()<<"music coder loaded";
            _state= false;
        }


    void loadFile(ofFileDialogResult data);


};