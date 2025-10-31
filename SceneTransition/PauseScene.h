#pragma once
#include "Scene.h"
#include <vector>
#include <map>
#include <string>
#include <functional>

/// <summary>
/// �|�[�Y�V�[��
/// </summary>
class PauseScene : public Scene
{
private:
	//���j���[���Ǝ��s���e�̑Ή��e�[�u��
	std::map<std::wstring, std::function<void()>> execTable_;
	int frame_ = 0;
	int selectIndex_ = 0;//���ݑI�𒆂̃C���f�b�N�X

	int yesnoIndex = 0;//No���f�t�H���g�ł����AYES = 0,NO = 1�Ƃ��܂�

	using UpdateFunc_t = void (PauseScene::*)(Input&);
	UpdateFunc_t update_;
	void AppearUpdate(Input& input);
	void NormalUpdate(Input& input);
	void DisappearUpdate(Input& input);

	void YesNoDialogUpdate(Input& input);

	using DrawFunc_t = void(PauseScene::*)();
	DrawFunc_t draw_;
	void IntervalDraw();
	void NormalDraw();
	std::vector<std::wstring> menuList_;//�|�[�Y��ʒ��ɕ\�����郁�j���[���X�g
	void DrawMenu();

	void YesNoDialogDraw();

public:
	PauseScene(SceneController& controller);
	void Update(Input& input)override;
	void Draw()override;
};

