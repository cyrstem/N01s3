# pragma once
#include "ofMain.h"

class Particle{
    public:

    glm::vec3 vel;
    ofPoint pos;
    glm::vec3 acc;
    ofPlanePrimitive plane;
    int age;
    float rotate;
    float alpha;
    bool dead;
    std::deque<ofPoint> logs;


    Particle(){
        pos = ofPoint(ofGetWindowWidth()/2,ofGetWindowHeight()/2);
        vel = glm::vec3(ofRandom(-5,5),ofRandom(-5,5),ofRandom(-5,5));
        acc = glm::vec3(0,0,0);

        plane.set(8,8,5,5,OF_PRIMITIVE_TRIANGLES);
    //variables ;;;
        age = 0;
        rotate =0;
        alpha = 255;
        dead = false;
   
    }

    void applyForce(glm::vec3 force){
        acc +=force;
    }

    void update(){

        vel+=acc;
        pos+= vel;
        //TAIL
        logs.push_front(pos);
        while(logs.size()>4){
            logs.pop_back();
        }

         age++;
         alpha --;


         if(alpha == 0){
            dead = true;
         }
         // rotate -= 0.05;

    }

    void draw(){

        ofSetColor(ofFloatColor(255.0,250.0,255.0),alpha);
    
        ofRotateZ(rotate);  
       
     
         plane.setPosition(pos);
    
       plane.draw();
       ofNoFill();
       ofBeginShape();
       for (ofPoint& log :this->logs)
       {
           ofVertex(log);
       }
       ofEndShape();
    
    }

    void reset(){
        //missing process to fix something  if it get in trouble 

    }

    

};