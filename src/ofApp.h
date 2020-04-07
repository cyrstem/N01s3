#pragma once

#include "ofMain.h"
#include "Visual/VisualSystem.h"
//#include "Particle.h"
#include "UI/UI.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		//send time
		float time;

	private:
		UI ui;

		VisualSystem v;
	

};

