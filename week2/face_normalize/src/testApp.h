#pragma once

#include "ofMain.h"
#include "ofxCv.h"

#include "ofxFaceTracker.h"

#include <dirent.h>

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	
	ofVideoGrabber cam;
	ofxFaceTracker tracker;
    
    ofImage img;
    
    string file_name;
    struct dirent* ent;
    DIR *pDir;
    int photo_num;
};
