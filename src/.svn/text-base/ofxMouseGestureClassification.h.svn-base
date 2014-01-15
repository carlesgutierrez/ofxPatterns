/*
 *  Author:
 *      Stjepan Rajko
 *      Arts, Media and Engineering Program
 *      Arizona State University
 *
 *  Copyright 2008 Arizona Board of Regents.
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


#ifndef OF_MOUSEGESTURECLASSIFICATION
#define OF_MOUSEGESTURECLASSIFICATION

#include "ofxPatternClassification.h"

// used to hold a single mouse postion
struct ofMousePosition
{
    ofMousePosition(int x, int y)
        : x(x)
        , y(y)
    {}
    int x;
    int y;
};

class MouseGestureClassificationConfiguration;

typedef ofPatternClassification<ofMousePosition, MouseGestureClassificationConfiguration> ofMouseGestureClassification;

#endif
