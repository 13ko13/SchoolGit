#include "PauseScene.h"
#include <DxLib.h>
#include "Input.h"
#include "SceneController.h"
#include "Application.h"

constexpr int frame_margin = 10;//�g����ʒ[����ǂꂭ�炢����Ă邩
constexpr int appear_interval = 10;//�g���o������܂ł̃t���[����
constexpr int menu_row_height = 50;//���j���[�̍s�̍���
constexpr int menu_left_margin = 200;//���j���[�g����̍��]��
constexpr int menu_top_margin = 120;//���j���[�g����̏�]��

void PauseScene::AppearUpdate(Input& input)
{
	if (frame_ == appear_interval)
	{
		update_ = &PauseScene::NormalUpdate;
		draw_ = &PauseScene::NormalDraw;
		frame_ = appear_interval;
		return;
	}
	++frame_;
}

void PauseScene::NormalUpdate(Input& input)
{
	if (input.IsTriggerd("pause"))
	{
		update_ = &PauseScene::DisappearUpdate;
		draw_ = &PauseScene::IntervalDraw;
		return;//�O�̂���return���Ă���
	}
	if (input.IsTriggerd("up"))
	{
		selectIndex_ = (selectIndex_ + menuList_.size() - 1) % menuList_.size();

	}
	if (input.IsTriggerd("down"))
	{
		selectIndex_ = (selectIndex_ + 1) % menuList_.size();
	}
}

void PauseScene::DisappearUpdate(Input& input)
{
	if (frame_ == 0)
	{
		controller_.PopScene();//���̎��_�Ŏ����͉�������
		return;
	}
	--frame_;
}

void PauseScene::IntervalDraw()
{
	const auto& wsize = Application::GetInstance().GetWindowSize();

	int center_y = wsize.h / 2;//��ʂ̐^�񒆂�Y���W
	float rate = static_cast<float>(frame_) /
		static_cast<float>(appear_interval);//�\������

	int frame_height = (wsize.h - frame_margin) - center_y;//�ŏI�I�ȃ|�[�Y�g�̍���
	frame_height *= rate;

	//�����ĐF�������Z���t�@����\��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(frame_margin,//��
		center_y - frame_height,//��
		wsize.w - frame_margin,//�E
		center_y + frame_height,//��
		0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�O�g
	DrawBox(frame_margin,//��
		center_y - frame_height,//��
		wsize.w - frame_margin,//�E
		center_y + frame_height,//��
		0xaaaaff, false, 3);
}

void PauseScene::NormalDraw()
{
	const auto& wsize = Application::GetInstance().GetWindowSize();
	//�����ĐF�������Z���t�@����\��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(frame_margin, frame_margin,//����
		wsize.w - frame_margin, wsize.h - frame_margin, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�O�g
	DrawBox(frame_margin, frame_margin,//����
		wsize.w - frame_margin, wsize.h - frame_margin, 0xaaaaff, false, 3);
	//�|�[�Y�V�[���̕�����\��
	DrawString(280, frame_margin + 20, L"Pause Scene", 0xffffff);
	DrawMenu();
}

void PauseScene::DrawMenu()
{
	int menuStartX = frame_margin + menu_left_margin;
	int indicatorX = menuStartX - 30;
	int menuY = frame_margin + menu_top_margin;
	for (int idx = 0; idx < menuList_.size(); ++idx)
	{
		int offsetX = 0;
		uint32_t col = 0xffffff;
		if (idx == selectIndex_)
		{
			DrawString(indicatorX, menuY, L"��", 0xffaaaa);
			offsetX = 10;
			col = GetColor(128, 255, 192);
		}
		DrawFormatString(menuStartX + offsetX, menuY,
			col,
			L"%s", menuList_[idx].c_str());

		menuY += menu_row_height;
	}
}

PauseScene::PauseScene(SceneController& controller) : Scene(controller),
update_(&PauseScene::AppearUpdate),
draw_(&PauseScene::IntervalDraw)
{
	menuList_ = {
		L"�Q�[���ɖ߂�",
		L"�L�[�R���t�B�O",
		L"�^�C�g���ɖ߂�",
		L"�Q�[�����I������"
	};
}

void PauseScene::Update(Input& input)
{
	(this->*update_)(input);
}

void PauseScene::Draw()
{
	(this->*draw_)();
}
