#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "Button.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void calculateRms();
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

		//sound staff 
		ofSoundPlayer song;
		float volume;
		float *fft;
		float *soundSpectrum;

		int bands;
		float decay ;
		static constexpr size_t nBandsToGet = 128;

		std::array<float,nBandsToGet> fftSmoothed{{0}};
		//buton late
		Button bnt;
		bool state;
	

};