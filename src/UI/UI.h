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
    volume =0.7;
     
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
};