#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(15);
    ofSetVerticalSync(true);


    //FBOS
    ofFboSettings s;
    s.width=ofGetWidth();
    s.height= ofGetHeight();
    s.internalformat =GL_RGBA;
    s.useDepth = true;
    s.useStencil = false;
    s.numSamples = 12;

    fbo.allocate(s);

    fbo.begin();
        ofClear(0);
    fbo.end();
    //camera stafff
    glm::vec3 center = glm::vec3(0,0,0);
    cam.lookAt(center);
    cam.setDistance(1600);



    
    sphere.set(700,12);

    ambient.setAmbientColor(ofFloatColor(ofColor::white));
    ambient.setPosition(0,0,0);

    time = ofGetElapsedTimeMillis();
  //basig ambirement set
   //ofEnableBlendMode(OF_BLENDMODE_ADD);
   ofEnableAntiAliasing();
   //ofEnableArbTex();
   ofEnableSmoothing();
   ofEnableDepthTest();
    


    //audio 
    //song.load("1.mp3");

    fft = new float[256];
    for (int i = 0; i < 128; i++)
    {
        fft[i] =0.5;

    }
    
    bands = 128;
           

}

//--------------------------------------------------------------
void ofApp::update(){

ofSoundUpdate();
song.setVolume(0.5);

soundSpectrum = ofSoundGetSpectrum(bands);
for (int i = 0; i < bands; i++)
{
    fft[i] *= 0.5;//decay 
    if (fft[i] < soundSpectrum[i])
    {
        fft[i] = soundSpectrum[i];
    }
}



    for (int i = 0; i < p.size(); i++)
    {
        p[i].update();
    }
    fbo.begin();
        ofClear(0);
    fbo.end();
}
//--------------------------------------------------------------
void ofApp::scene(){
     vertices = sphere.getMesh().getVertices();
    for (int i = 0; i < vertices.size(); i++)
    {
        glm::vec3 v = vertices[i];
        if(ofGetFrameNum() % 70  ==0){
            Particle pTemp;
            pTemp.pos = v +ofPoint(0,0,0);
            pTemp.rotate += ofRandom(0,180);
            p.push_back(pTemp);
        }
    }
   
    fbo.begin();
        cam.begin();

             for (int i = 0; i < p.size(); i++)
        {   

             p[i].draw();

            if ( p[i].dead == true)
            {
                p.erase(p.begin()); 
            }
         
        }


        cam.end();


      ofPushStyle();
       ofSetColor(ofColor::red);
       for (int j= 0; j < bands; j++)
       {
            for (int i = 0; i < bands; i++)
            {
            ofDrawRectangle(0,10 + i* 20,fft[i]* 1000,10);
            }
       }
       
      
       
       
        ofPopStyle();
    fbo.end();

}
//--------------------------------------------------------------
void ofApp::draw(){
    scene();
    fbo.draw(0,0);

   
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'f')
    {
        ofToggleFullscreen();
    }
    
    if (key =='p')
    {
        song.play();
    }
        if (key =='0')
    {
        song.stop();
    }
    if (key =='o')
    {
        ofFileDialogResult music = ofSystemLoadDialog("load a song");
        if (music.bSuccess)
        {   
             ofLog()<<"file selected";
            loadFile(music);
        }else
        {
            ofLog()<<"file not selected";
        }
        
        
    }
    
    
}
//--------------------------------------------------------------
void ofApp::loadFile(ofFileDialogResult data){

    ofFile file (data.getPath());



    if(file.exists()){
        songs.clear();
        song.unloadSound();
        ofLog()<<file.getAbsolutePath();
        song.load(file);
    }

}
//--------------------------------------------------------------