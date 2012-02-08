#include "testApp.h"
#include "ofAppGlutWindow.h"

int main() {
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 500, 700, OF_WINDOW);
	ofRunApp(new testApp());
}
