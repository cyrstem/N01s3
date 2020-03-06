#pragma once

#include "ofMain.h"

class Button
{
    public:
        Button();
        ~Button();
        ofEvent<ofVec2f> clickedInside;
        ofTrueTypeFont font;

    void setup(int radius, int x, int y, ofColor color);
    void draw();
    void clear();

    //We need to declare all this mouse events methods to be able to listen to mouse events.
    //All this must be declared even if we are just going to use only one of this methods.
    void mouseMoved(ofMouseEventArgs& args);
    void mouseDragged(ofMouseEventArgs& args);
    void mousePressed(ofMouseEventArgs& args);
    void mouseReleased(ofMouseEventArgs& args);
    void mouseScrolled(ofMouseEventArgs& args);
    void mouseEntered(ofMouseEventArgs& args);
    void mouseExited(ofMouseEventArgs& args);

    //this function checks if the passed arguments are inside the circle.
    bool inside(float _x, float _y);
    int radius, x, y;
    ofColor color;
    string  _state;

protected:
    bool bRegisteredEvents;
        
};