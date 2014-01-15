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

#ifndef _TEST_APP
#define _TEST_APP

#include <iostream>
#include <fstream>

#include "ofxVectorGestureRecognition.h"

#include "ofMain.h"

using namespace std;

class testApp : public ofSimpleApp{

	public:
        testApp() : frame(0), recording(false), testing(false) {}

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
	
		//extra protect
		bool checkCleanRecodings(vector<vector<vector<double> > > _recordings);

    private:
	
		void startPath();
		void stopPath();

        // the recorded gestures used for training
        vector<vector<vector<double> > > recordings;
        // the actual observation used for recognition
        vector<double> observation;
        // mouse position buffer
        vector<vector<double> > mousepositions;

        // current frame
        int frame;
        // flag indicating whether we are recording a gesture
        bool recording;
        // flag indicating whether we are in testing mode (vs. training mode)
        bool testing;
        // last recognized gesture
        int numRecogGesture;

        // the object used for recognition of a set of gestures
        ofVectorGestureRecognition recognition;
};

#endif

