#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup() {    
    ofImgL.load("left.png");
    ofImgR.load("right.png");
    
    ofImgR.setImageType(OF_IMAGE_GRAYSCALE); // you can also use cvtColor(src,dest,COLOR_BGR2GRAY);
    ofImgL.setImageType(OF_IMAGE_GRAYSCALE);
    
    imgMatL = toCv(ofImgL);
    imgMatR = toCv(ofImgR);
    
    cv::StereoBM sbm; // stereo block matching
    //fiddle-able parameters
    sbm.state->SADWindowSize = 15;
    sbm.state->numberOfDisparities = 112;
    sbm.state->preFilterSize = 5;
    sbm.state->preFilterCap = 1;
    sbm.state->minDisparity = -10;
    sbm.state->textureThreshold = 5;
    sbm.state->uniquenessRatio = 5;
    sbm.state->speckleWindowSize = 40;
    sbm.state->speckleRange = 60;
    sbm.state->disp12MaxDiff = 64;
    
    sbm(imgMatL, imgMatR, stereoMat); // Calculate the diaparity and save into stereoMat
    
    normalize(stereoMat, stereoMat2, 0.1, 255, CV_MINMAX, CV_8U);
    
    // stereoMat is 16 bit signed -> stereoMat2 is 8 bit unsigned
    // important step, or else the values will be blown out when the image is drawn
    
    
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackground(0);
    
    drawMat(stereoMat2, 50, 245);
    
    ofImgR.draw(  0,0, 320,240);
    ofImgL.draw(330,0, 320,240);  
}

