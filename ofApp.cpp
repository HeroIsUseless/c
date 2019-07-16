#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// 建立面板
	gui.setup();
	gui.add(rectVisible.setup("ball visible", true));
	gui.add(color.setup("color", 255, 0, 255)); // 颜色
	gui.add(length.setup("length", 100, 0, 100)); // 长度
	gui.add(rotate.setup("rotate", 360, 0, 360)); // 旋转
	gui.add(ballVisible.setup("ball visible",false));
	gui.add(ballRotate.setup("ball rotate", true));

	// 设置背景
	ofBackground(100);
	// 设置光源
	ofSetSmoothLighting(true);
	pointLight.setDiffuseColor(ofFloatColor(0.9, 0.9, 0.9)); // 设置弥漫光颜色
	// 设置物体
	sphere.setRadius(100);
	material.setShininess(120); // 平滑化
}

//--------------------------------------------------------------
void ofApp::draw(){
	gui.draw();
	if (ballVisible) {
		cam.setGlobalPosition({ 0,0,cam.getImagePlaneDistance(ofGetCurrentViewport()) }); // 设定摄像机位置
		cam.begin();
		sphere.setPosition(0, 0, 0); // 中心为坐标原点
		sphere.rotateDeg(ballRotate, 0, 1.0, 0.0); // 进行旋转
		ofNoFill(); // 这里是画出外面的框架
		ofSetColor(255, 255, 255);
		sphere.setScale(1.01f);
		sphere.drawWireframe();
		sphere.setScale(1.f);
		cam.end();
	}
	if (rectVisible) {
		ofTranslate(400, 300, 0); // 设置坐标
		ofRotate(rotate, 0, 0, 1); // 摄像机旋转
		ofSetColor(color);
		ofFill();
		ofDrawRectangle(-50, -50, 0, length, length);
	}
}
