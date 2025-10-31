#include "KeyConfigScene.h"
#include <DxLib.h>
#include "Input.h"
#include "SceneController.h"

KeyConfigScene::KeyConfigScene(SceneController& controller):Scene(controller)
{
}

void KeyConfigScene::Update(Input& input)
{
	if (input.IsTriggerd("ok"))
	{
		controller_.PopScene();
	}
}

void KeyConfigScene::Draw()
{
	//キーコンフィグの
	DrawBox(320 - 150, 240 - 100, 320 + 150, 240 + 100, 0x00aa00, true);
	//キーコンフィグの外枠
	DrawBox(320 - 150, 240 - 100, 320 + 150, 240 + 100, 0xffffff, false,3);
	//キーコンフィグのテキスト
	DrawString(280, 240, L"KeyCOnfig Scene", 0xffffff);
}
