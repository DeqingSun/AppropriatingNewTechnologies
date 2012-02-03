/*
 *  face_trick.cpp
 *  face_trick
 *
 *  Created by Sun Deqing on 1/29/12
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "face_trick.h"

extern "C" {
#include "macGlutfix.h"
}


//--------------------------------------------------------------
void face_trick::setup() {
	//CGContextRef cgctx = NULL;
	//ofSetVerticalSync(true);
    ofSetFrameRate(15);
	tex.allocate(320,240, GL_RGBA);
	img.allocate(320,240, OF_IMAGE_GRAYSCALE);
  //  mask_img.allocate(569,782, OF_IMAGE_COLOR_ALPHA);
 //   mask_img.setUseTexture(true);
    mask_img.loadImage("mask.png");
	ofEnableAlphaBlending();
    finder.setup("haarcascade_frontalface_default.xml");
    finder.setNeighbors(3);
	
    
}


//--------------------------------------------------------------
void face_trick::update() {
	int w = 320;
	int h = 240;
	
	unsigned char * data = pixelsBelowWindow(ofGetWindowPositionX(),ofGetWindowPositionY(),w,h);
	
	// now, let's get the R and B data swapped, so that it's all OK:
	for (int i = 0; i < w*h; i++){
		// input format  ARGB
        // output format RGBA
        
        unsigned char r1 = data[i*4]; // mem A  
        data[i*4]   = data[i*4+1];   
        data[i*4+1] = data[i*4+2];   
        data[i*4+2] = data[i*4+3];   
        data[i*4+3] = r1;   
        
	}
	
	
	if (data!= NULL) tex.loadData(data, 320,240, GL_RGBA);
    
 //   unsigned char temp [300*300];
  //  for (int i = 0; i < w*h; i++){
  //      temp[i] = data[i*4];                
//	}
    
   // setFromPixels(...)
    img.setFromPixels(data, w, h, OF_IMAGE_COLOR_ALPHA, true);
    //img.setImageType(OF_IMAGE_GRAYSCALE);
    img.setImageType(OF_IMAGE_COLOR);
    finder.findHaarObjects(img,20,20);
 //   img
    
    
	//cout << imageBelowWindow()[0] << endl;

}


//--------------------------------------------------------------
void face_trick::draw() {
  /*  ofSetColor(255,130,0);
	float radius = 50 + 10 * sin(1);
	ofFill();		// draw "filled shapes"
	ofCircle(100,400,radius);*/
   // tex.draw(0,0, ofGetWidth(), ofGetHeight());
    tex.draw(0,0, 320,240);
    img.draw(320,0, 320,240);
    //ofSetColor (255, 255, 255);
    //mask_img.draw(0,300, 50, 100);
    
	ofNoFill();
  //  printf("%d\n",finder.blobs.size());
	for(int i = 0; i < finder.blobs.size(); i++) {
		ofRectangle cur = finder.blobs[i].boundingRect;
		//ofRect(cur.x, cur.y, cur.width, cur.height);
        mask_img.draw(cur.x, cur.y, cur.width, cur.height);
	}
}


//--------------------------------------------------------------
void face_trick::keyPressed( int key ) {
	
}


//--------------------------------------------------------------
void face_trick::keyReleased( int key ) {
	
}


//--------------------------------------------------------------
void face_trick::mouseMoved( int x, int y ) {
	
}


//--------------------------------------------------------------
void face_trick::mouseDragged( int x, int y, int button ) {
	
}


//--------------------------------------------------------------
void face_trick::mousePressed( int x, int y, int button ) {
	
}


//--------------------------------------------------------------
void face_trick::mouseReleased( int x, int y, int button ) {
	
}


//--------------------------------------------------------------
void face_trick::windowResized( int w, int h ) {
	
}
