#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    pDir=opendir ("/Users/sundeqing/Documents/of_preRelease_v007_osx/apps/my_app/cross_correlation/bin/data/resized");
    
    
    
    
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
                    my_filenames.push_back(ent->d_name);
                    //string curFilename = "resized/";
                    //file_name=ent->d_name;
                    //curFilename.append(ent->d_name);
                    //img.loadImage(curFilename);
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
    
    for (int i=0;i<my_filenames.size();i++){
        pic_mean[i]=-1;   
    }
    
    printf ("got %lu files\n",my_filenames.size());
    loop_i=1;
    loop_j=0;
    
    
    pFile = fopen ("/Users/sundeqing/Documents/of_preRelease_v007_osx/apps/my_app/cross_correlation/bin/data/myfile.txt","w");
       
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    if (loop_i>=0){
        string curFilename = "resized/";
        curFilename.append(my_filenames.at(loop_i));
     //   cout  << curFilename << endl;
        img.loadImage(curFilename);
        int w=130;
        int h=130;
        img.crop(50+171-w/2, 50+170+40-h/2, w, h);
        img.setImageType(OF_IMAGE_GRAYSCALE);
        curFilename = "resized/";
        curFilename.append(my_filenames.at(loop_j));
        img2.loadImage(curFilename);
        img2.crop(50+171-w/2, 50+170+40-h/2, w, h);
        img2.setImageType(OF_IMAGE_GRAYSCALE); 
        
        
        
        
        
        int texW = img.width;
        int texH = img.height;
        int all_pixels=texW*texH;
        
        // allocate the pixels:
        //unsigned char my_pixels[texW*texH];
        
        
        //----------------------------- copy pixels from image to texPixels
        unsigned char * data1 = img.getPixels();
        unsigned char * data2 = img2.getPixels();
        
        if (pic_mean[loop_i]<0){ //get avg
            unsigned int sum; 
            for (int x= 0; x< all_pixels;x++){
                sum+=data1[x];
            }
            pic_mean[loop_i]=sum/(all_pixels);
            printf ("%d avg %d \n",loop_i,pic_mean[loop_i]);
        }
        if (pic_mean[loop_j]<0){ //get avg
            unsigned int sum; 
            for (int x= 0; x< all_pixels;x++){
                sum+=data2[x];
            }
            pic_mean[loop_j]=sum/(all_pixels);
            printf ("%d avg %d \n",loop_j,pic_mean[loop_j]);
        }
        
        //normalized cross correlation
        //http://www.mathworks.com/help/toolbox/images/ref/normxcorr2.html
        int cross_correlation=0;
        float auto_correlation_1=0,auto_correlation_2=0;
        int avg_1=pic_mean[loop_i];
        int avg_2=pic_mean[loop_j];
        
        for (int x= 0; x< all_pixels;x++){
            cross_correlation+=(data1[x]-avg_1)*(data2[x]-avg_2);
            auto_correlation_1+=(data1[x]-avg_1)*(data1[x]-avg_1);
            auto_correlation_2+=(data2[x]-avg_2)*(data2[x]-avg_2);
        }
        
        float denominator=sqrt(auto_correlation_1*auto_correlation_2);
        int nor_cc_65535=65535*(float)cross_correlation/denominator;
        
             printf ("normalized cross correlation:%d and %d is %d\n",loop_i,loop_j,nor_cc_65535);

        
            fprintf (pFile, "%d %d %d\n",loop_i,loop_j,nor_cc_65535);
        

        
        
        
        
        
        
        
 /*       if (pic_mean[loop_i]<0){
            
            for (int x= ; x< ;x++){
                
                
            }
            
        }*/
        
        
    //    cout  << loop_i << " " << loop_j << endl;

    }else{
        fclose (pFile);
        ofExit();
    }
    
        
    
   /* if (loop_i>=my_filenames.size()){
        loop_i=0;
        loop_j++;
        if (loop_i>=my_filenames.size()){
        
        
    }*/
    
}

//--------------------------------------------------------------
void testApp::draw(){
    if (loop_i>=0) {
        
        
        ofSetColor(255);
        img.draw(0,0);
        img2.draw(500,0);
        int w=130;
        int h=130;
        ofNoFill();
      //  ofRect(50+171-w/2, 50+170+40-h/2, w, h);
       // ofRect(500+50+171-w/2, 50+170+40-h/2, w, h);
        
        
        
        loop_i++;
        if (loop_i>=my_filenames.size()){
            loop_j++;
            if (loop_j>=my_filenames.size()-1){
                loop_i=-1;
            }else{
                loop_i=loop_j+1;
            }
        }
        
    
    }
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