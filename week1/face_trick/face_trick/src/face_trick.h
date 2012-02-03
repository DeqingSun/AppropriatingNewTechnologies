/*
 *  face_trick.h
 *  face_trick
 *
 *  Created by Sun Deqing on 1/29/12
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _face_trick_APP
#define _face_trick_APP

#include "ofMain.h"
#include "ofxCvHaarFinder.h"


class face_trick : public ofBaseApp {
	
  public:
	
	void setup();
	void update();
	void draw();
	
	void keyPressed( int key );
	void keyReleased( int key );
	void mouseMoved( int x, int y );
	void mouseDragged( int x, int y, int button );
	void mousePressed( int x, int y, int button );
	void mouseReleased( int x, int y, int button );
	void windowResized( int w, int h );
    
    ofTexture	tex;
    ofImage img,mask_img;
    ofxCvHaarFinder finder;
	
};

#endif
