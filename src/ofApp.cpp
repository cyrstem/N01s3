#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(15);
    ofSetVerticalSync(true);
    ui.set();
    v.enviroment();
   ofEnableAntiAliasing();
   ofEnableSmoothing();
   ofEnableDepthTest();

}
//--------------------------------------------------------------
void ofApp::update(){

ui.set();

ofSoundUpdate();

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
      //song.getVolume();
       //volume = song.getVolume()+1;
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