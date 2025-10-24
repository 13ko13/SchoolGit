#pragma once
#include "Scene.h"

/// <summary>
/// �^�C�g���V�[��
/// </summary>
class TitleScene : public Scene//Scene����p������TitleScene
{
private:
	int titleH_;//�^�C�g���摜�n���h��
	int titleLogoH_;//�^�C�g�����S�n���h��
	int frame_;//�o�߃t���[��

	//�����o�ϐ��|�C���^���g�p���ē�����Ԃ�����������
	//update�֐���draw�֐����A���݂�TitleScene�̏�Ԃɍ��킹��
	//�؂�ւ��Ă���
	void FadeInUpdate(Input&);//�t�F�[�h�C��Update
	void NormalUpdate(Input&);//�ʏ�Update
	void FadeOutUpdate(Input&);//�t�F�[�h�A�E�gUpdate

	using UpdateFunc_t = void(TitleScene::*)(Input&);
	UpdateFunc_t update_;

	void NormalDraw();//�ʏ�Draw
	void FadeDraw();//�t�F�[�hDraw
	using DrawFunc_t = void(TitleScene::*)();
	DrawFunc_t draw_;//Draw�֐������ł��郁���o�֐��|�C���^
public:
	TitleScene(SceneController&);
	void Update(Input&)override;
	void Draw() override;
};

