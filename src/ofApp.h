#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "UI/UI.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void env();
		void update();
		void scene();
		void draw();
	    //void loadFile(ofFileDialogResult data);
		void keyPressed(int key);
		void drawCorner(ofPoint p);
		//send time
		float time;
		//sphere 
		ofSpherePrimitive sphere;
		// remplacement of this  ofSpherePrimitive sphere;
		// with a mesh

		ofMesh mesh;

		//cam
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


		//luz stafff
		ofLight ambient ,areaLight ,spot;
		ofMaterial material;
	public:
		//sound staff 
		ofSoundPlayer song;
		//moving UI to UI class
		UI ui;
	

};

