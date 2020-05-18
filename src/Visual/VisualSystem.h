#pragma once
#include "ofMain.h"
#include "Particle.h"
class VisualSystem
{


public:

    VisualSystem();

    void enviroment();

    void scene();

    void show();

    void reset();

void drawCorner(ofPoint p);
        //variables  
       // ofSpherePrimitive sphere;
        ofIcoSpherePrimitive ico_sphere;




    	ofEasyCam cam;
		//ofCamera cam;
		glm::vec3 centro;
		ofFbo fbo;
        //particle  call  should improve  later;
		vector<Particle> p;
		bool dead;
        //save vertices  // maybe not needed here 
		vector<glm::vec3> vertices;
		//shaders

        ofLight ambient ,areaLight ,spot;
		ofMaterial material;
        float spinX;
};
