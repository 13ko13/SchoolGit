#include "GameoverScene.h"
#include "../Input.h"
#include <DxLib.h>
#include "TitleScene.h"
#include "SceneController.h"
using namespace std;

GameoverScene::GameoverScene(SceneController& controller) : 
	Scene(controller)
{
}

void GameoverScene::Update(Input& input)
{
	if (input.IsTriggerd("ok"))
	{
		controller_.ChangeScene(std::make_shared<TitleScene>(controller_));
		return;
	}
}

void GameoverScene::Draw()
{
	DrawString(250, 240, L"Game Over Scene", 0xffffff);
}