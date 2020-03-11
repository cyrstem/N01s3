#pragma once

#include "ofMain.h"

class Button
{
    public:
        Button();
        ~Button();
        ofEvent<ofVec2f> clickedInside;

    void setup(int radius, int x, int y, ofColor color);
    void draw();
    void clear();
    void mouseMoved(ofMouseEventArgs& args);
    void mouseDragged(ofMouseEventArgs& args);
    void mousePressed(ofMouseEventArgs& args);
    void mouseReleased(ofMouseEventArgs& args);
    void mouseScrolled(ofMouseEventArgs& args);
    void mouseEntered(ofMouseEventArgs& args);
    void mouseExited(ofMouseEventArgs& args);

    bool inside(float _x, float _y);
    int radius, x, y;
    ofColor color;

protected:
    bool bRegisteredEvents;
        
};