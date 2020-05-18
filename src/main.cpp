#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
	//ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:


	ofGLFWWindowSettings settings;
	settings.setGLVersion(3,3);
	settings.setSize(1200,800);
	settings.decorated= false; //removes windows icons 
	settings.setPosition(glm::vec2(380,100));
	 ofCreateWindow(settings);

	ofRunApp(new ofApp());

}
