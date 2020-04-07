#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(15);
    ofSetVerticalSync(true);
    ui.set();
    v.enviroment();
//     time = ofGetElapsedTimeMillis();

   ofEnableAntiAliasing();
   //ofEnableArbTex();
   ofEnableSmoothing();
   ofEnableDepthTest();

}
//--------------------------------------------------------------
void ofApp::update(){

ui.set();

ofSoundUpdate();
//song.setVolume(0.7);


    // for (int i = 0; i < p.size(); i++)
    //     {
    //         p[i].update();
    //     }

    
    v.reset();
}

//--------------------------------------------------------------
void ofApp::draw(){

    ui.show();
    v.show();

}
//--------------------------------------------------------------
 void ofApp::keyPressed(int key){


     if (key == 's')
     {
        ofLog()<<"stop song";
        ui.m.song.stop();
     }
     
    if (key == 'f')
    {
        ofToggleFullscreen();
    }
    if (key == OF_KEY_UP)
    {
      // volume++;
    }
    if (key == OF_KEY_DOWN)
    {
       //volume--;
    }

    
    // if (key =='p')
    // {
        
    //     if (song.isLoaded() ==false)
    //     {
    //         ofLog()<<"Load something first ";
    //        ui.state = true;
            
    //     }else{
    //         song.play();
    //     }
        
    // }
    //     if (key =='0')
    // {
    //     song.stop();
    // }
    
 }