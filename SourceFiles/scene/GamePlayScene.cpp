#include "GamePlayScene.h"
#include <imgui.h>
#include <opencv2/opencv.hpp>

void GamePlayScene::Initialize()
{
	debugCamera.Initialize({ 0,0 });
	viewProjection.Initialize();
	viewProjection.eye.y = 350;
	viewProjection.eye.z = -75;
	viewProjection.target.z = 10;
	stage.Initialize();
	ModelManager::SetViewProjection(&debugCamera);

	fm.Initialize();
	fm.SetFont("resources/Inkfree.ttf", 16, 34);
}

void GamePlayScene::Update()
{
	if (input->IsTrigger(Key::_1)) { ModelManager::SetViewProjection(&viewProjection); }
	if (input->IsTrigger(Key::_2)) { ModelManager::SetViewProjection(&debugCamera); }
	debugCamera.Update();
	stage.Update();

	//レンダリング
	fm.DrawString("Hello World!");
	image = fm.GetImage();
}

void GamePlayScene::Draw()
{
	cv::Mat image_cv(200, 500, CV_8UC1, image);
	cv::imshow("クアッドホッケー", image_cv);
}