#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
	
public:
	void setup();
	void draw();

	ofxPanel gui; // 面板
	ofxToggle rectVisible; // 球存在
	ofxFloatSlider length; // 半径
	ofxFloatSlider rotate; // 旋转
	ofxFloatSlider color; // 颜色

	ofxToggle ballVisible; // 球存在
	ofxToggle ballRotate; // 球存在
	ofIcoSpherePrimitive sphere; // 球体 
	ofLight pointLight; // 点光源
	ofMaterial material; // 材质
	float spinY = 1; // 旋转速度
	ofCamera cam;
};

