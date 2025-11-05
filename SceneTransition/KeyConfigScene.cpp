#include "KeyConfigScene.h"
#include <DxLib.h>
#include "Input.h"
#include "SceneController.h"
#include "Application.h"
#include "StringFunctions.h"

constexpr int appear_interval = 10;//枠が出現するまでのフレーム数
constexpr int menu_row_height = 50;//メニューの行の高さ
constexpr int menu_left_margin = 150;//メニュー枠からの左余白
constexpr int menu_top_margin = 120;//メニュー枠からの上余白

KeyConfigScene::KeyConfigScene(SceneController& controller,Input& input):
	Scene(controller),
	input_(input),
	update_(&KeyConfigScene::AppearUpdate),
	draw_(&KeyConfigScene::IntervalDraw),
	frame_(0)
{
}

void KeyConfigScene::AppearUpdate(Input&)
{
	if (++frame_ >= appear_interval)
	{
		update_ = &KeyConfigScene::NormalUpdate;
		draw_ = &KeyConfigScene::NormalDraw;
	}
}

void KeyConfigScene::NormalUpdate(Input& input)
{
	if (input.IsTriggerd("ok"))
	{
		update_ = &KeyConfigScene::DisappearUpdate;
		draw_ = &KeyConfigScene::IntervalDraw;
		frame_ = appear_interval;
		return;
	}
}

void KeyConfigScene::DisappearUpdate(Input&)
{
	if (--frame_ <= 0)
	{
		controller_.PopScene();
	}
}

void KeyConfigScene::IntervalDraw()
{
	const auto& wsize = Application::GetInstance().GetWindowSize();
	const int frame_size_w = wsize.w - 10;
	const int frame_size_h = wsize.h - 10;
	const int center_y = wsize.h / 2;
	const int center_x = wsize.w / 2;

	float rate = static_cast<float>(frame_) / static_cast<float>(appear_interval);
	int frameWidth = frame_size_w * rate;

	//キーコンフィグの背景
	DrawBox(
		center_x - frameWidth / 2,
		center_y - frame_size_h / 2,
		center_x + frameWidth / 2,
		center_y + frame_size_h / 2,
		0x44aa44, true);
	//キーコンフィグの外枠
	DrawBox(
		center_x - frameWidth / 2,
		center_y - frame_size_h / 2,
		center_x + frameWidth / 2,
		center_y + frame_size_h / 2,
		0x00aa00, false, 3);
}

void KeyConfigScene::NormalDraw()
{
	const auto& wsize = Application::GetInstance().GetWindowSize();
	const int frame_size_w = wsize.w - 10;
	const int frame_size_h = wsize.h - 10;
	const int center_y = wsize.h / 2;
	const int center_x = wsize.w / 2;
	//キーコンフィグの背景
	DrawBox(
		center_x - frame_size_w / 2,
		center_y - frame_size_h / 2,
		center_x + frame_size_w / 2,
		center_y + frame_size_h / 2,
		0x44aa44, true);


	//キーコンフィグの外枠
	DrawBox(
		center_x - frame_size_w / 2,
		center_y - frame_size_h / 2,
		center_x + frame_size_w / 2,
		center_y + frame_size_h / 2,
		0x00aa00, false, 3);

	//キーコンフィグのテキスト
	DrawString(center_x - 50, center_y - frame_size_h / 2 + 10, L"KeyConfig", 0xffffff);

	int y = center_y - frame_size_h / 2;
	y += 100;
	int x = center_x - frame_size_w / 2 + menu_left_margin;
	for (const auto& row : input_.inputTable_)
	{
		auto name = StringFunctions::WStringFromString(row.first);
		DrawFormatString(x, y, 0xffffff, L"%s", name.c_str());
		y += 50;
	}
}

void KeyConfigScene::Update(Input& input)
{
	(this->*update_)(input);
}

void KeyConfigScene::Draw()
{
	(this->*draw_)();
}
