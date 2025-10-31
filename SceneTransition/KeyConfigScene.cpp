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
	//�L�[�R���t�B�O��
	DrawBox(320 - 150, 240 - 100, 320 + 150, 240 + 100, 0x00aa00, true);
	//�L�[�R���t�B�O�̊O�g
	DrawBox(320 - 150, 240 - 100, 320 + 150, 240 + 100, 0xffffff, false,3);
	//�L�[�R���t�B�O�̃e�L�X�g
	DrawString(280, 240, L"KeyCOnfig Scene", 0xffffff);
}
