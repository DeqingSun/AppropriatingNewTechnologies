/*
 *  main.cpp
 *  face_trick
 *
 *  Created by Sun Deqing on 1/29/12
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"
#include "ofAppGlutWindow.h"
#include "face_trick.h"


int main( ) {
	
	// Setup the GL context
    ofAppGlutWindow window;
    
    // Sets up the window aspect and mode
    // screenMode [ OF_WINDOW | OF_FULLSCREEN | OF_GAME_MODE ]
	ofSetupOpenGL( &window, 640,240, OF_WINDOW );
	
	// Begins the openGL cycle of the application
	ofRunApp( new face_trick() );
}
