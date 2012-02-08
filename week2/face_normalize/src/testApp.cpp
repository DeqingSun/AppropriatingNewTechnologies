#include "testApp.h"

#include <string.h>



using namespace ofxCv;

void testApp::setup() {
//	string curFilename = "images/ab3615.jpg";
 //   img.loadImage(curFilename);
    ofSetVerticalSync(true);
	ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
    tracker.setup();
	tracker.setRescale(.5);
    tracker.setIterations(25);
//    tracker.setTolerance(1);
//    tracker.setClamp(0);
    tracker.setAttempts(4); 
    
    pDir=opendir ("/Users/sundeqing/Documents/of_preRelease_v007_osx/addons/ofxFaceTracker/example-empty/bin/data/images");
    
    ofSetFrameRate(2);
    photo_num=0;
}

void testApp::update() {
    if (pDir != NULL) {
        
        /* print all the files and directories within directory */
        while ((ent = readdir (pDir))){
            if ( ent != NULL) {
                printf ("%s\n", ent->d_name);
                if (strstr (ent->d_name,".jpg")!=NULL){
                    //printf ("%s\n", "OPEN");
                    string curFilename = "images/";
                    file_name=ent->d_name;
                    curFilename.append(ent->d_name);
                    img.loadImage(curFilename);
                    tracker.update(toCv(img));
                    break;
                }else{
                    continue;
                }
            }else{
                closedir (pDir);
                pDir=NULL;
                break;
            }
        }
        
    }else{
        printf ("%s\n", "XXXXX");
        
    }
    
       // while ((ent = readdir (dir)) != NULL) {
            
      //  }
  //  closedir (dir);
    
    
	//cam.update();
	//if(cam.isFrameNew()) {
		
	//}
}

void testApp::draw() {
	if (pDir != NULL) {
        ofSetColor(255);
        //img.crop(-10,-10,100,100);
        //img.resize(100,100);
        //img.draw(0,0);
        
        //    ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
        
        ofSetLineWidth(1);
        //	tracker.draw();
        
        ofPolyline leftEye = tracker.getImageFeature(ofxFaceTracker::LEFT_EYE);
        ofPolyline rightEye = tracker.getImageFeature(ofxFaceTracker::RIGHT_EYE);
        vector<ofPoint> v = leftEye.getVertices();
        int left_eye_x,left_eye_y;
        int right_eye_x,right_eye_y;
        int eyes_center_x,eyes_center_y,eyes_distance;
        
        int b_l=v.at(0).x;
        int b_u=v.at(0).y;
        int b_r=v.at(0).x;
        int b_d=v.at(0).y;
        for(int i=0; i<v.size(); i++) { //get bounder of eye
            if (b_u>v.at(i).y) b_u=v.at(i).y;
            if (b_d<v.at(i).y) b_d=v.at(i).y;
            if (b_l>v.at(i).x) b_l=v.at(i).x;
            if (b_r<v.at(i).x) b_r=v.at(i).x;
        }
        left_eye_x=(b_l+b_r)/2; //calculate center of eye
        left_eye_y=(b_u+b_d)/2;
        
        v = rightEye.getVertices();
        b_l=v.at(0).x;
        b_u=v.at(0).y;
        b_r=v.at(0).x;
        b_d=v.at(0).y;
        for(int i=0; i<v.size(); i++) { //get bounder of eye
            if (b_u>v.at(i).y) b_u=v.at(i).y;
            if (b_d<v.at(i).y) b_d=v.at(i).y;
            if (b_l>v.at(i).x) b_l=v.at(i).x;
            if (b_r<v.at(i).x) b_r=v.at(i).x;
        }
        right_eye_x=(b_l+b_r)/2; //calculate center of eye
        right_eye_y=(b_u+b_d)/2;
        eyes_center_x=(right_eye_x+left_eye_x)/2;
        eyes_center_y=(right_eye_y+left_eye_y)/2;
        eyes_distance=right_eye_x-left_eye_x;
        
        //img.setAnchorPoint(eyes_center_x,eyes_center_y);
        img.resize(img.getWidth()*60/eyes_distance, img.getHeight()*60/eyes_distance);
        img.draw(50+171-eyes_center_x*60/eyes_distance,50+170-eyes_center_y*60/eyes_distance);
        
        ofImage myImage;
        myImage.grabScreen(0,0,500,700);
        string curFilename = "images/resized/";
        string str_num = ofToString(photo_num);
        string str_num2 = "";
        for (int i=0;i<3-str_num.length();i++){
            str_num2.append("0");
        }
        str_num2.append(str_num);
        curFilename.append(str_num2);
        curFilename.append("_");
        photo_num++;
        curFilename.append(file_name.substr(0,file_name.find_last_of('.')));
        curFilename.append(".png");
        //printf ("%s \n",curFilename);
        cout  << curFilename << endl;
        myImage.saveImage(curFilename);

        /*ofSetColor(ofColor::yellow);
         ofCircle(left_eye_x,left_eye_y, 2);
         ofCircle(right_eye_x,right_eye_y, 2);*/
        
        printf ("%d %d %d\n", (left_eye_x+right_eye_x)/2, (left_eye_y+right_eye_y)/2,eyes_distance);    
        
        
        
        
        
        /*   ofSetLineWidth(2);
         ofSetColor(ofColor::red);
         leftEye.draw();
         // ofRect(b_l, b_u, b_r-b_l, b_d-b_u);
         ofSetColor(ofColor::green);
         rightEye.draw();*/  

        }
}

void testApp::keyPressed(int key) {
	if(key == 'r') {
		tracker.reset();
	}
}