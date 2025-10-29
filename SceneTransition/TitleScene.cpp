#include "TitleScene.h"
#include <DxLib.h>
#include"Input.h"
#include "GameScene.h"
#include "SceneController.h"
#include "Application.h"

//�t�F�[�h�ɂ�����t���[����
constexpr int fade_interval = 60;

TitleScene::TitleScene(SceneController& controller) :
	Scene(controller)
{
	titleH_ = LoadGraph(L"img/title.png");
	titleLogoH_ = LoadGraph(L"img/game_title.png");
	//update��draw�̊֐��|�C���^��FadeInUpdate��FadeDraw���Q�Ƃ�����
	update_ = &TitleScene::FadeInUpdate;
	draw_ = &TitleScene::FadeDraw;
	frame_ = fade_interval;
}

void TitleScene::FadeInUpdate(Input&)
{
	if (--frame_ <= 0)
	{
		update_ = &TitleScene::NormalUpdate;
		draw_ = &TitleScene::NormalDraw;
		return;
	}
}

void TitleScene::NormalUpdate(Input& input)
{
	if (input.IsTriggerd("ok"))
	{
		update_ = &TitleScene::FadeOutUpdate;
		draw_ = &TitleScene::FadeDraw;
		frame_ = 0;//�t�F�[�h�A�E�g�̍ŏ��@�O�̂���
		return;//�厖
	}
}

void TitleScene::FadeOutUpdate(Input&)
{
	if (++frame_ >= fade_interval)
	{
		controller_.ChangeScene(std::make_shared<GameScene>(controller_));
		return;
	}
}

void TitleScene::NormalDraw()
{
	const auto& wsize = Application::GetInstance().GetWindowSize();
	DrawRotaGraph(wsize.w / 2, wsize.h / 2, 1.0f, 0.0f, titleH_, true);
	DrawRotaGraph(wsize.w / 2, wsize.h / 2, 0.75f, 0.0f, titleLogoH_, true);
}

void TitleScene::FadeDraw()
{
	const auto& wsize = Application::GetInstance().GetWindowSize();
	DrawRotaGraph(320, 240, 1.0f, 0.0f, titleH_, true);
	DrawRotaGraph(320, 240, 0.75f, 0.0f, titleLogoH_, true);
	//�l�͈̔͂���������0.0�`1.0�ɂ��Ă����Ƃ��낢��ƈ����₷���Ȃ�܂�
	auto rate = static_cast<float>(frame_) / static_cast<float>(fade_interval);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * rate);//���u�����h
	DrawBox(0, 0, wsize.w, wsize.h, 0x000000, true);//��ʑS�̂ɍ��t�B������������
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//�u�����h���Ȃ�
}

void TitleScene::Update(Input& input)
{
	(this->*update_)(input);//���݊��蓖�Ă��Ă��郁���oUpdate�n�֐������s����
}

void TitleScene::Draw()
{
	(this->*draw_)();//���蓖�Ă��Ă���Draw�n�����o�֐������s����
}
