#include "testApp.h"
#include <dirent.h>

//--------------------------------------------------------------
void testApp::setup(){
    unsigned char opt[]={69,64,162,135,168,58,98,65,11,195,152,111,124,107,137,87,8,72,150,167,126,35,147,191,169,159,205,71,19,81,74,115,61,99,106,185,179,70,104,146,116,154,101,170,21,88,109,17,197,63,46,187,151,55,181,37,78,201,103,32,163,14,83,82,148,129,38,120,26,125,190,47,149,173,180,193,16,96,121,131,200,76,59,1,153,20,39,123,77,158,105,95,27,79,43,24,34,30,68,117,36,142,119,136,182,203,67,97,189,128,57,48,184,10,44,138,100,91,52,160,157,166,122,25,178,18,7,155,84,6,140,130,53,192,5,139,15,41,175,4,56,94,93,92,62,9,66,86,108,31,40,161,113,23,28,133,127,196,42,174,60,22,144,202,198,176,134,172,114,3,45,164,75,199,73,102,89,186,165,204,33,13,49,145,2,143,12,90,188,194,50,177,110,183,171,132,118,112,85,156,51,141,80,54,29
    };
    
    //printf("%d \n",opt[204]);
     DIR *pDir=opendir ("/Users/sundeqing/Documents/of_preRelease_v007_osx/apps/my_app/cross_correlation/bin/data/resized");
    string file_name;
    struct dirent* ent;
    
    char temp[50];
    
    int n1,n2;
    
    while(pDir != NULL) {
        
        /* print all the files and directories within directory */
        while (1){
            ent = readdir (pDir);
            //printf ("%d\n", ent);
            if ( ent != NULL) {
                //  printf ("%s\n", ent->d_name);
                if (strstr (ent->d_name,".png")!=NULL){
                    //printf ("%s\n", "OPEN");
                    
                    printf ("%s\n", ent->d_name);
                    strncpy(temp,ent->d_name,3);
                    n1=ofToInt(temp);
                    //printf ("%d\n", n1);
                    for (int i=0;i<205;i++){
                        if (opt[i]==n1+1){
                            n2=i;
                            break;
                        }
                    }
                    string str_num = ofToString(n2);
                    string str_num2 = "";
                    for (int i=0;i<3-str_num.length();i++){
                        str_num2.append("0");
                    }
                    str_num2.append(str_num);
                    string curFilename = "/Users/sundeqing/Desktop/final";
                    curFilename.append("/");
                    curFilename.append(str_num2);
                    curFilename.append("_");
                    curFilename.append(ent->d_name);
                    printf ("%s\n", curFilename.c_str());
                    
                    string source_file = "/Users/sundeqing/Documents/of_preRelease_v007_osx/apps/my_app/cross_correlation/bin/data/resized/";
                    source_file.append(ent->d_name);
                    
                    ofFile::copyFromTo(source_file,curFilename,false,false);

                    
                    break;
                }else{
                    continue;
                }
            }else{
                printf ("end dir\n");
                closedir (pDir);
                pDir=NULL;
                break;
            }
        }
        
    }
    ofExit();
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}