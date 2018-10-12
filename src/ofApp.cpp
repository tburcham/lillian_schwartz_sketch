#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofLog() << "GL Version" << glGetString( GL_VERSION );
    
    
    vid.setup(640, 480);
    
    midiIn.listInPorts();
    midiIn.openPort(0);
    midiIn.addListener(this);
    
    ofLog() << "Video Initialized" << endl;
    ofLog() << "Midi Initialized" << endl;
    
    panel.setup("", "settings.xml", 10, 100);
    
    panel.add(brightnessThreshold.setup("brightness threshold", 127, 0, 255));
    panel.add(depth.setup("depth", 100, 0, 1000));
    panel.add(spacing.setup("spacing", 10, 0, 100));
    panel.add(width.setup("width", 10, 0, 100));
    panel.loadFromFile("settings.xml");
    
}

//--------------------------------------------------------------
void ofApp::update(){

    vid.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);
    
    
    cam.begin();
    //cam.enableOrtho();
    
    
    
    //vid.draw(vid.getWidth(), 0);
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    parentMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    parentMesh.clearVertices();
    
    int width = 5;
    int depth = 300;
    int spacing = 5;
    int brightnessThreshold = 127;
    
    for (int i = 0; i < vid.getWidth(); i+=spacing) {
        
        for (int j = 0; j < vid.getHeight(); j+=spacing) {
            
            ofColor color = vid.getPixels().getColor(i, j);
            if (color.getBrightness() <  brightnessThreshold) {
                
                ofPushMatrix();
                
                // Map to screen space
                ofPoint coords;
                coords.x = ofMap(i, 0, vid.getWidth(), -ofGetWidth()/2, ofGetWidth()/2);
                coords.y = ofMap(j, 0, vid.getHeight(), ofGetHeight()/2, -ofGetHeight()/2);
                
                ofTranslate(coords);
                
                mesh = ofMesh::box(width, width, depth*ofMap(color.getBrightness(), brightnessThreshold, 255, 0, 1));
                
                ofSetColor(color);
                mesh.draw();
                
                //parentMesh.append(mesh);
                
                ofPopMatrix();
                
            }
            
            
        }
        
    }
    
    //parentMesh.draw();
    //mesh.draw();
    
    cam.end();
    
    ofSetColor(255, 255, 255);
    if (!bHide) {
        panel.draw();
        // ofDisableDepthTest();
    } else {
        //ofEnableDepthTest();
    }
}


//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& message) {
    
    switch(message.control) {
        case 21:
            brightnessThreshold = ofMap(message.value, 0, 127, brightnessThreshold.getMin(), brightnessThreshold.getMax());
            break;
        case 22:
            depth = ofMap(message.value, 0, 127, depth.getMin(), depth.getMax());
            break;
        case 23:
            spacing = ofMap(message.value, 0, 127, spacing.getMin(), spacing.getMax());
            break;
        case 24:
            width = ofMap(message.value, 0, 127, width.getMin(), width.getMax());
            break;
//        case 25:
//            speed = ofMap(message.value, 0, 127, speed.getMin(), speed.getMax());
//            break;
//        case 26:
//            numShapes = ofMap(message.value, 0, 127, numShapes.getMin(), numShapes.getMax());
//            break;
        default:
            cout << message.control << " not assigned" << endl;
            
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's') {
        mesh.save("lillian.ply");
    }
    if(key == 'h'){
        bHide = !bHide;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
