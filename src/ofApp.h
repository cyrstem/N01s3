#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "Button.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void scene();
		void draw();
		void loadFile(ofFileDialogResult data);
		void onMouseInButton(ofVec2f& e);
		void keyPressed(int key);
		void drawCorner(ofPoint p);

		ofTrueTypeFont font;

		//send time
		float time;
		//sphere
		ofSpherePrimitive sphere;
		//cam
		ofEasyCam cam;
		//ofCamera cam;
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

		//sound staff 
		ofSoundPlayer song;
		float *fft;
		float *soundSpectrum;
		float  fftchosen;

		vector<float>lfh;
		void findMax();

		int bands;
		float decay ;
		//float bang*;
		float* bang;

		//buton late
		Button bnt;
		bool state;
		float fX,fY,fZ;


};