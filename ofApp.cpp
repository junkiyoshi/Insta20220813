#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetWindowTitle("openFrameworks");
	ofSetFrameRate(30);

	ofBackground(255);
	ofSetColor(0);
	ofNoFill();
	ofSetLineWidth(3);
	ofEnableDepthTest();
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
	for (int x = -330; x <= 330; x += 30) {

		for (int y = -330; y <= 330; y += 30) {

			ofPushMatrix();
			ofTranslate(x, y);

			auto distance = glm::length(glm::vec2(x, y));
			
			auto x_value = ofNoise(noise_seed.x, distance * 0.001 - ofGetFrameNum() * 0.01);
			auto y_value = ofNoise(noise_seed.y, distance * 0.001 - ofGetFrameNum() * 0.01);
			auto z_value = ofNoise(noise_seed.z, distance * 0.001 - ofGetFrameNum() * 0.01);

			auto x_deg = x_value < 0.35 ? ofMap(x_value, 0, 0.35, -180, 0) : x_value > 0.75 ? ofMap(x_value, 0.75, 1, 0, 180) : 0;
			auto y_deg = y_value < 0.35 ? ofMap(y_value, 0, 0.35, -180, 0) : y_value > 0.75 ? ofMap(y_value, 0.75, 1, 0, 180) : 0;
			auto z_deg = z_value < 0.35 ? ofMap(z_value, 0, 0.35, -180, 0) : z_value > 0.75 ? ofMap(z_value, 0.75, 1, 0, 180) : 0;

			ofRotateZ(z_deg);
			ofRotateY(y_deg);
			ofRotateX(x_deg);

			ofFill();
			ofSetColor(0, 0, 255, 128);
			ofDrawRectangle(glm::vec2(), 30, 30);

			ofNoFill();
			ofSetColor(0, 0, 255);
			ofDrawRectangle(glm::vec2(), 30, 30);

			ofPopMatrix();
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}