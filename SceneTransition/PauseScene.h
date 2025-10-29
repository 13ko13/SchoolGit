#pragma once
#include "Scene.h"
#include <vector>
#include <map>
#include <string>

/// <summary>
/// �|�[�Y�V�[��
/// </summary>
class PauseScene : public Scene
{
private:
	int frame_ = 0;
	int selectIndex_ = 0;//���ݑI�𒆂̃C���f�b�N�X

	using UpdateFunc_t = void (PauseScene::*)(Input&);
	UpdateFunc_t update_;
	void AppearUpdate(Input& input);
	void NormalUpdate(Input& input);
	void DisappearUpdate(Input& input);

	using DrawFunc_t = void(PauseScene::*)();
	DrawFunc_t draw_;
	void IntervalDraw();
	void NormalDraw();
	std::vector<std::wstring> menuList_;//�|�[�Y��ʒ��ɕ\�����郁�j���[���X�g
	void DrawMenu();

public:
	PauseScene(SceneController& controller);
	void Update(Input& input)override;
	void Draw()override;
};

