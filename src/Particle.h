# pragma once
#include "ofMain.h"

class Particle{
    public:
    Particle(){
        pos = ofPoint(ofGetWindowWidth()/2,ofGetWindowHeight()/2);
        vel = glm::vec3(ofRandom(-1,1),ofRandom(-1,1),ofRandom(-1,1));
        plane.set(15,15,6,6,OF_PRIMITIVE_TRIANGLES);
        age = 0;
        rotate =0;
        alpha = 255;
        dead = false;
    
    }

    void update(){
        pos+= vel;

         age++;
         alpha --;


         if(alpha == 0){
            dead = true;
         }

    }

    void draw(){
        ofSetColor(ofColor::white ,alpha);
      
        ofRotateZ(rotate);  
       
         plane.setPosition(pos);
    
         plane.drawVertices();
     
      
    
    }
void reset(){
}


glm::vec3 vel;
ofPoint pos;
ofPlanePrimitive plane;
int age;
float rotate;
float alpha;
bool dead;

};