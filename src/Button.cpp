#include "Button.h"

Button::Button() {
	bRegisteredEvents = false;
    font.load("font.ttf",13,true,false);
}

Button::~Button(){
	clear();
}

void Button::setup(int radius, int x, int y, ofColor color) {
    this->radius = radius;
    this->x = x;
    this->y = y;
    this->color = color;



    if (!bRegisteredEvents) {
        ofRegisterMouseEvents(this); // this will enable our Button class to listen to the mouse events.
        bRegisteredEvents = true;
    }


}

void Button::draw() {


    ofPushStyle();
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofSetColor(color);
        font.drawString(" File ",x-35,y+10);
    ofPopStyle();
   
   
}

void Button::clear() {
    if (bRegisteredEvents) {
        ofUnregisterMouseEvents(this); // disable listening to mouse events.
        bRegisteredEvents = false;
    }
}


void Button::mouseMoved(ofMouseEventArgs& args) {}
void Button::mouseDragged(ofMouseEventArgs& args) {}
void Button::mousePressed(ofMouseEventArgs& args) {}
void Button::mouseReleased(ofMouseEventArgs& args) {
    if (inside(args.x, args.y)) {
        // if the mouse is pressed over the Button an event will be notified (broadcasted) 
        // the ButtonEvent object will contain the mouse position, so this values are accesible to any class that is listening.
        ofVec2f mousePos = ofVec2f(args.x, args.y);
        ofNotifyEvent(clickedInside, mousePos, this);
       // ofNotifyEvent(clickedInsideGlobal, mousePos);
    }
}
void Button::mouseScrolled(ofMouseEventArgs& args) {}
void Button::mouseEntered(ofMouseEventArgs& args) {}
void Button::mouseExited(ofMouseEventArgs& args) {}

//this function checks if the passed arguments are inside the Button.
bool Button::inside(float _x, float _y) {
    return (ofVec2f(_x, _y).distance(ofVec2f(x, y)) < radius);
}