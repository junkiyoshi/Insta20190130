#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(2.5);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	float scale = 30;
	ofColor color;

	this->cam.begin();
	ofRotateX(-90);

	for (int v = 0; v < 360; v += 6) {

		glm::vec2 noise_point = glm::vec2(cos(v * DEG_TO_RAD), sin(v * DEG_TO_RAD));
		float noise_value = ofNoise(noise_point.x, noise_point.y, ofGetFrameNum() * 0.03);
		scale = noise_value > 0.65 ? ofMap(noise_value, 0.65, 1, 20, 30) : 20;

		int tmp_v = v;
		for (int u = -180; u <= 180 - 6; u += 6) {
			
			ofSetColor(239, 39, 39);
			ofBeginShape();
			ofVertex(this->make_apple_point((u - 3) * DEG_TO_RAD, (tmp_v - 3) * DEG_TO_RAD) * scale);
			ofVertex(this->make_apple_point((u - 9) * DEG_TO_RAD, (tmp_v - 3) * DEG_TO_RAD) * scale);
			ofVertex(this->make_apple_point((u - 3) * DEG_TO_RAD, (tmp_v + 3) * DEG_TO_RAD) * scale);
			ofVertex(this->make_apple_point((u + 3) * DEG_TO_RAD, (tmp_v + 3) * DEG_TO_RAD) * scale);
			ofEndShape();

			ofSetColor(39);
			ofDrawLine(this->make_apple_point((u + 3) * DEG_TO_RAD, (tmp_v + 3) * DEG_TO_RAD) * scale, this->make_apple_point((u - 3) * DEG_TO_RAD, (tmp_v - 3) * DEG_TO_RAD) * scale);
			ofDrawLine(this->make_apple_point((u - 3) * DEG_TO_RAD, (tmp_v + 3) * DEG_TO_RAD) * scale, this->make_apple_point((u - 9) * DEG_TO_RAD, (tmp_v - 3) * DEG_TO_RAD) * scale);

			tmp_v += 6;
		}
	}	

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_apple_point(float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち リンゴ局面 apple surface P.33 

	float x = (4 + 3.8 * cos(u)) * cos(v);
	float y = (4 + 3.8 * cos(u)) * sin(v);
	float z = -5 * log10(1 - 0.315 * u) + 5 * sin(u) + 2 * cos(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
