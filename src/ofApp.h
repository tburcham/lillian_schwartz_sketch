#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp, public ofxMidiListener{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    
        ofVideoGrabber vid;
        ofEasyCam cam;
        ofMesh mesh;
        ofMesh parentMesh;
    
        void newMidiMessage(ofxMidiMessage& message);
        ofxMidiIn midiIn;
    
        ofxPanel panel;
        ofxFloatSlider brightnessThreshold;
        ofxFloatSlider depth;
        ofxFloatSlider spacing;
        ofxFloatSlider width;
    
        bool bHide;
};
