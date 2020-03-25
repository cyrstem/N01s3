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
    centro = glm::vec3(0,0,0);
    cam.lookAt(centro);
    cam.setPosition(glm::vec3(0,0,2200));


    sphere.set(700,12);
    //lights
    ambient.setAmbientColor(ofFloatColor(ofColor::whiteSmoke));
    ambient.setPosition(0,0,0);
    ambient.setScale(20);

    spot.setPointLight();
    spot.setPosition(0,0,100);
    spot.setDiffuseColor(ofFloatColor(255,255,122));
    spot.setSpecularColor(ofFloatColor(255,255,155));
    spot.setSpotConcentration(45);
    spot.setSpotlightCutOff(50);
    spot.enable();



    areaLight.setup();
    areaLight.enable();
    areaLight.setAreaLight(1500,1500);
    areaLight.setAmbientColor(ofFloatColor(1.0,0.1,0.1));
    areaLight.setAttenuation(1.0,1.0001,0.0001);
    areaLight.setDiffuseColor(ofFloatColor(1,1,1));
    areaLight.setSpecularColor(ofFloatColor(1,0,1));
    areaLight.rotateDeg(0,glm::vec3(1,0,0));
    areaLight.rotateDeg(-45,glm::vec3(1,0,0));
    areaLight.setPosition(0,150,-100);


    material.setAmbientColor(ofFloatColor(0.1,0.1,0.1,1.0));
	material.setDiffuseColor(ofFloatColor(0.8,0.8,0.8,1.0));
	material.setSpecularColor(ofFloatColor(0.8,0.8,0.8,1.0));
	material.setShininess(10);



    time = ofGetElapsedTimeMillis();
    //basic ambient setup 0
   ///ofEnableBlendMode(OF_BLENDMODE_ADD);
   ofEnableAntiAliasing();
   //ofEnableArbTex();
   ofEnableSmoothing();
   ofEnableDepthTest();
   volume = 1.0;
  
    
    fft = new float[256];
    for (int i = 0; i < 128; i++)
    {
        fft[i] =0.6;

    }
    
    bands = 128;
    
    bnt.setup(100,ofGetWidth()/2,ofGetHeight()-35,ofColor::red);
      ofAddListener(bnt.clickedInside, this, &ofApp::onMouseInButton);
    

}

//--------------------------------------------------------------
void ofApp::calculateRms(){
    // float rms = 0.0;
    // int numCounted = 0;
    // for (int i = 0; i <256; i++)
    // {
    //     float leftSample = input[i*2] *0.5;
    //     float rightSample = input[i*2]*0.5;
    //     rms += leftSample *leftSample;
    //     rms += rightSample *rightSample;
    //     numCounted +=2;

    // }
    // rms/=(float)numCounted;
    // rms =sqrt(rms);
}

//--------------------------------------------------------------
void ofApp::update(){

float  *val = ofSoundGetSpectrum(nBandsToGet);
for (int i = 0; i < nBandsToGet; i++)
{
    fftSmoothed[i] *= 0.96f;
    if (fftSmoothed[i] <val [i]) fftSmoothed[i] =val[i];
    
}

ofSoundUpdate();
song.setVolume(volume);

// soundSpectrum = ofSoundGetSpectrum(bands);
//     for (int i = 0; i < bands; i++)
//     {
//         fft[i] *= 0.5f;//decay 
//         if (fft[i] < soundSpectrum[i])
//         {
//             fft[i] = soundSpectrum[i]; 
//         }

//     }


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

     // this part is for controling born rate of the particle  still neeed  to work 
    // it seems  to  work but not  for the aplication  as i  first imagine 

      glm::vec3 force(ofRandom(-5.0,5.0),ofRandom(-5.1,5.0),ofRandom(-5.1,5.1));

    // int born = ofMap(fftchosen,20,110,30,80);


    for (int i = 0; i < vertices.size(); i++)
    {
        glm::vec3 v = vertices[i];
        if(ofGetFrameNum() % 60  == 0){
            Particle pTemp;
            pTemp.pos = v + ofPoint(0,0,0);
            pTemp.rotate += ofRandom(0,180);
            pTemp.applyForce(force);
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
             material.begin();  
             p[i].draw();
             material.end();
            if ( p[i].dead == true)
            {
                p.erase(p.begin()); 
            }
         
        }
    


   //areaLight.draw();
   //ambient.draw();
  // spot.draw();


        cam.end();

//helper for the  audio bands

    ofPushStyle();
       ofSetColor(ofColor::red);
       ofFill();
        float width = (float)(5*128)/nBandsToGet;
        for (int i = 0; i < nBandsToGet; i++)
        {
            ofDrawRectangle(65+i*width,ofGetHeight()-20,width,-(fftSmoothed[i]* 200));
        }
        

    //    for (int j= 0; j < bands; j++)
    //    {
    //         for (int i = 0; i < bands; i++)
    //         {
    //             ofDrawRectangle(0,10 + i* 20,fft[i]* 1000,10);
    //         }
    //    }   
     ofPopStyle();

       
    fbo.end();

}
//--------------------------------------------------------------
void ofApp::draw(){
   scene();
    bnt.draw();
        //findMax();
   fbo.draw(0,0);
  
    if (state ==true)
    {
        ofDrawBitmapString(ofToString(volume),ofGetWidth()-65,ofGetHeight()-20);
    }
    else
    {
        ofDrawBitmapString("volume "+ofToString(volume),ofGetWidth()-95,ofGetHeight()-20);
    }
    
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'f')
    {
        ofToggleFullscreen();
    }
    if (key == OF_KEY_UP)
    {
       volume++;
    }
    if (key == OF_KEY_DOWN)
    {
       volume--;
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


//--------------------------------------------------------------
void ofApp::drawCorner(ofPoint p){
    float pl = 100.0;
    ofDrawLine(p.x,p.y,p.z,p.x,p.y,p.z -sin(p.z)*pl);
    ofDrawLine(p.x,p.y,p.z,p.x,p.y-sin(p.z)*pl,p.z);
    ofDrawLine(p.x,p.y,p.z,p.x-sin(p.z)*pl,p.y,p.z);
}