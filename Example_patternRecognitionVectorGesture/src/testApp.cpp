/*
 *  Authors:
 *      Stjepan Rajko
 *      Arts, Media and Engineering Program
 *      Arizona State University
 *
 *      David Burri
 *      Berner Fachhochschule
 *      Signal and Image Processing Lab, TI Burgdorf
 *
 *  Copyright 2009 David Burri, Arizona Board of Regents.
 *
 *  This file is part of the AME Patterns openFrameworks addon.
 *
 *  The AME Patterns openFrameworks addon is free software: you can redistribute it
 *  and/or modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation, either version 3 of the License,
 *  or (at your option) any later version.
 *
 *  The AME Patterns openFrameworks addon is distributed in the hope that it will be
 *  useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with the AME Patterns openFrameworks addon.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

 /*
  * Modified by Carles Gutierrez by adding methods (checkCleanRecodings) before add vectors to train data
  * Adapted to OF08 OSX
 */

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(255,255,255);
	
	ofSetWindowTitle("mouse gesture recognition example");

	ofSetFrameRate(50); // mouse measurements are not precise enough for high framerates.

	numRecogGesture = 0;

	frame = 0;

}

//--------------------------------------------------------------
void testApp::update(){
	
    observation.assign(2,0); // Add to values with 0 

    // direction vector is used as feature
    if(recording || testing) {

        mousepositions.push_back(vector<double>(2,0));
        mousepositions.back()[0] = mouseX;
        mousepositions.back()[1] = mouseY;

        int size = mousepositions.size();

        if((size > 1)) {
            observation[0] = mousepositions[size-1][0] - mousepositions[size-2][0];
            observation[1] = mousepositions[size-1][1] - mousepositions[size-2][1];

            // normalize direction vector
            if(observation[0] != 0 ||  observation[1] != 0) {
                double factor = sqrt(observation[0]*observation[0] + observation[1]*observation[1]);
                observation[0] /= factor;
                observation[1] /= factor;
            }
        }
    }

    // if recording, just record the current movement observation
    if(recording && observation.size() > 1) {
		recordings.back().push_back(observation);
    }

    // if we're testing and the training succeeded, recognize
    if(testing && (recognition.numPatterns() > 0)) {
        numRecogGesture = recognition.match(observation);

        // delete mousepositions
        while(mousepositions.size() > 100)
             mousepositions.erase(mousepositions.begin(),mousepositions.begin()+1);
    }

    frame++;

}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofFill();

	ofSetHexColor(0x000000);
    ofDrawBitmapString(
    "Instructions:\n\nYou will start in training mode.  Hold down the mouse button while executing a training sample with the mouse\n"
    "(e.g., an S-like shape) to record it. Repeat a few times for the same pattern (e.g., record an S-like shape multiple times),\n"
    "and then hit \"t\" to train a model.\n"
    "If you'd like, train a few more models (e.g., repeat training for a few more types of shapes),\n"
    "then hit space to switch to testing mode. In testing mode, just move the mouse and the system should automatically pick out\n"
    "gesture executions (no need to hold down the button).\n"
    "Note: for this example, the position or scale of the gesture should not impact the recognition.\n\n"
    "Please see the documentation for copyright and license information.\n"
    "Example and underlying ofxPatterns / AME Patterns code by:\n\n    David Burri and Stjepan Rajko\n"
    "\nModified by Carles Gutierrez by adding methods (checkCleanRecodings) before add vectors to train data"
					   , 20, 450);

    if(testing) {
        ofSetHexColor(0x008F00);
        ofDrawBitmapString("last recognized gesture: " + ofToString( (int)recognition.lastRecognition() ), 20, 50);

    } else {
        ofSetHexColor(0x8F0000);
    	ofDrawBitmapString("number of recorded gestures (hit 'c' to clear, or 't' to train): " + ofToString((int)recordings.size()), 20, 50);
    }

	ofSetHexColor(0x000000);
    ofDrawBitmapString("trained gestures (hit the space bar to switch between training and testing): " + ofToString( (int)(recognition.numPatterns()) ), 20, 30);

    ofDrawBitmapString("hit 's' or 'l' to save or load the gesture models.", 20, 70);

    // display the last recorded gesture
    if(!mousepositions.empty()) {
        int size = mousepositions.size();
        int numDisplayed = testing ? (std::min)(size, 5) : size;
        if (recognition.lastRecognition() > 0)
            numDisplayed = (std::min)(size, recognition.lastRecognitionLength() - 1);
            
        for(int i = size - numDisplayed; i < size; i++) {
            double color_ratio = double(i) / size;
            ofSetColor(0, 0, 0);
            ofCircle(mousepositions[i][0],mousepositions[i][1],4);

            ofSetColor(255*color_ratio,0,255*(1-color_ratio),255);
            ofCircle(mousepositions[i][0],mousepositions[i][1],3);

            if(i > size - numDisplayed)
                ofLine(mousepositions[i][0], mousepositions[i][1], mousepositions[i-1][0], mousepositions[i-1][1]);
        }
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    switch(key)
    {
		case 's' :
		{
			// save the gestures
			std::ofstream out("gesture.models", std::ios::binary);
			recognition.save(out);
		}
            break;
        case 'l' :
		{
			// save the gestures
			std::ifstream in("gesture.models", std::ios::binary);
			if(in.is_open())
				recognition.load(in);
		}
            break;
        case 't' :
			//To prevent error while pressing path
			stopPath();
			
            // train the gesture using the recorded examples
			if(!recordings.empty()) {
				if(checkCleanRecodings(recordings) == true){ 
					recognition.addPatternWithExamples(recordings, 10);
					recordings.clear();
				}
			}
			//recording = false;
            recordings.clear();
			mousepositions.clear();
			break;
        case 'c' :
			//To prevent error while pressing path
			stopPath();
			
			cout << "Cleaning recordings" << endl;
            recordings.clear();
            mousepositions.clear();
			cout << "Clears done" << endl;
            break;
			
        case ' ' :
            testing = !testing;
            recordings.clear();
            mousepositions.clear();
            recognition.clear();
            recording = false;
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){

}

//--------------------------------------------------------------
bool testApp::checkCleanRecodings(vector<vector<vector<double> > > _recordings){

	bool bclean;
	bclean = true;
	int counterGeneral;
	counterGeneral = 0;
	
	for(int i=0; i< recordings.size(); i++){
		
		int counterSize, countIntems;
		counterSize = 0;
		countIntems = 0;
		
		for(int j=0; j< _recordings[i].size(); j++){
			counterSize += _recordings[i][j].size();
			countIntems ++;					
		}
		cout << "counterSize[" << i << "]" << "= " << counterSize << "]" << endl;
		cout << "countIntems = " << countIntems << endl;
		
		bool betwice;
		betwice = false;
		
		if(countIntems < 5) betwice = true;
		
		bclean = bclean * !betwice;
		
		counterGeneral += counterSize;
	}
	
	cout << "Final repor:: bclean=" << bclean << endl;
	cout << "Final repor:: = _recordings.size() [" << _recordings.size() << "]" << endl; 	
	
	return bclean;
}

//--------------------------------------------------------------
void testApp::startPath(){
	
    // if we are in testing mode, we don't need to record
    if(testing)
        return;
	
    // start recording a gesture example
    recordings.push_back(vector<vector<double> >());
    recording = true;
    mousepositions.clear();
	
}

//--------------------------------------------------------------
void testApp::stopPath(){

    if(testing)
        return;
	
    //stop recording
    recording = false;
	
    // if the recording is empty, discard it
    if(recordings.back().empty())
        recordings.pop_back();

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
	startPath();
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
	stopPath();
}



