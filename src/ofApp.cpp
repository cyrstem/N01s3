#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(15);
    ofSetVerticalSync(true);
    state = false;

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

    //------camera stafff
    glm::vec3 center = glm::vec3(0,0,0);
    cam.lookAt(center);
    cam.setDistance(1900);



    
    sphere.set(700,12);

    ambient.setAmbientColor(ofFloatColor(ofColor::white));
    //ambient.setPosition(0,500,500);

    time = ofGetElapsedTimeMillis();
    //basic ambient setup 0
   //ofEnableBlendMode(OF_BLENDMODE_ADD);
   ofEnableAntiAliasing();
   //ofEnableArbTex();
   ofEnableSmoothing();
   ofEnableDepthTest();
    
    fft = new float[256];
    for (int i = 0; i < 128; i++)
    {
        fft[i] =0.5;

    }
    
    bands = 128;
    bnt.setup(100,ofGetWidth()/2,ofGetHeight()-35,ofColor::red);
      ofAddListener(bnt.clickedInside, this, &ofApp::onMouseInButton);
    

}

//--------------------------------------------------------------
void ofApp::update(){

ofSoundUpdate();
song.setVolume(0.7);

soundSpectrum = ofSoundGetSpectrum(bands);
    for (int i = 0; i < bands; i++)
    {
        fft[i] *= 0.8;//decay 
        if (fft[i] < soundSpectrum[i])
        {
            fft[i] = soundSpectrum[i];
            //ofLog()<<fft[3];
            
        }
        if (i==0)    
        {
            lfh.push_back(fft[i]*450 +100);
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
        if(ofGetFrameNum()% 70  ==0){
            Particle pTemp;
            pTemp.pos = v + ofPoint(0,0,0);
            pTemp.rotate += ofRandom(0,180);
            p.push_back(pTemp);
        }
    }
   
    fbo.begin();
        cam.begin();
        ambient.enable();

        //here goes the markers 

for (int x = -1  ; x <= 1; x+=2)
   {
       for (int y = -1; y <=1; y+=2)
       {
           for (int z = -1; z < 1; z+=2)
           {
               ofPushStyle();
               ofSetColor(ofColor::red);
               drawCorner(ofPoint(x*(1500/2+10),y*(1500/2+10),z*(10+10)));
               ofPopStyle();
           }
           
       }
       
   }





             for (int i = 0; i < p.size(); i++)
        {   

             p[i].draw();

            if ( p[i].dead == true)
            {
                p.erase(p.begin()); 
            }
         
        }
    






        cam.end();

//helper for the  audio bands

      ofPushStyle();
       ofSetColor(ofColor::red);
       for (int j= 0; j < bands; j++)
       {
            for (int i = 0; i < bands; i++)
            {
                ofDrawRectangle(0,10 + i* 20,fft[0]* 1000,10);
            }
       }
       
      
       
       
        ofPopStyle();

//ofSetColor(ofColor::white);  

  
        
    fbo.end();

}
//--------------------------------------------------------------
void ofApp::draw(){
   scene();
    bnt.draw();

        findMax();
   fbo.draw(0,0);
  
    if (state ==true)
    {
        ofDrawBitmapString(ofToString(song.getPositionMS()),ofGetWidth()-65,ofGetHeight()-20);
    }
    else
    {
        ofDrawBitmapString(" 0:0 ",ofGetWidth()-65,ofGetHeight()-20);
    }
    
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'f')
    {
        ofToggleFullscreen();
    }
    
    if (key =='p')
    {
        
        if (song.isLoaded() ==false)
        {
            ofLog()<<"Load something first ";
            state = true;
            
        }else{
            song.play();
        }
        
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
             state = true;
            loadFile(music);
        }else
        {
            ofLog()<<"file not selected";
            state= false;
        }
        
        
    }
    
    
}
//--------------------------------------------------------------
void ofApp::loadFile(ofFileDialogResult data){

    ofFile file (data.getPath());
    if(file.exists()){
        song.unloadSound();
        ofLog()<<file.getAbsolutePath();
        song.load(file);
    }
    if(song.isLoaded()){
        state = true;
        song.play();
    }else{
        ofLog()<<"at least load a file ";
        state = false;
    }

}
//--------------------------------------------------------------
void ofApp::onMouseInButton(ofVec2f & e){

cout << "botton pendejo" << endl;

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

void ofApp::findMax(){
    float max;

    max = lfh[0];
    for (int i = 0; i < lfh.size() -1; i++)
    {
        if (lfh[i + 1]>lfh[i])
        {
            max = lfh[i + 1];
        }
        
    }
    ofDrawBitmapString(ofToString(max),ofGetWindowWidth()-65,50);
    
}


void ofApp::drawCorner(ofPoint p){
    float pl = 100.0;
    ofDrawLine(p.x,p.y,p.z,p.x,p.y,p.z -sin(p.z)*pl);
    ofDrawLine(p.x,p.y,p.z,p.x,p.y-sin(p.z)*pl,p.z);
    ofDrawLine(p.x,p.y,p.z,p.x-sin(p.z)*pl,p.y,p.z);
}