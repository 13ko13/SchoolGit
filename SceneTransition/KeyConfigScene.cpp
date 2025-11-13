#include "KeyConfigScene.h"
#include <DxLib.h>
#include "Input.h"
#include "SceneController.h"
#include "Application.h"
#include "StringFunctions.h"
#include <array>

constexpr int appear_interval = 10;//枠が出現するまでのフレーム数
constexpr int menu_row_height = 50;//メニューの行の高さ
constexpr int menu_left_margin = 80;//メニュー枠からの左余白
constexpr int menu_top_margin = 120;//メニュー枠からの上余白

KeyConfigScene::KeyConfigScene(SceneController& controller, Input& input) :
	Scene(controller),
	input_(input),
	update_(&KeyConfigScene::AppearUpdate),
	draw_(&KeyConfigScene::IntervalDraw),
	frame_(0)
{
	input.tempInputTable_ = input.inputTable_;
	keyNameTable_[KEY_INPUT_BACK] = L"BackSpaceキー";
	keyNameTable_[KEY_INPUT_TAB] = L"Tabキー";
	keyNameTable_[KEY_INPUT_RETURN] = L"Enterキー";
	keyNameTable_[KEY_INPUT_LSHIFT] = L"左Shiftキー";
	keyNameTable_[KEY_INPUT_RSHIFT] = L"右Shiftキー";
	keyNameTable_[KEY_INPUT_LCONTROL] = L"左Ctrlキー";
	keyNameTable_[KEY_INPUT_RCONTROL] = L"右Ctrlキー";
	keyNameTable_[KEY_INPUT_ESCAPE] = L"Escキー";
	keyNameTable_[KEY_INPUT_SPACE] = L"Spaceキー";
	keyNameTable_[KEY_INPUT_A] = L"Ａキー";
	keyNameTable_[KEY_INPUT_B] = L"Ｂキー";
	keyNameTable_[KEY_INPUT_C] = L"Ｃキー";
	keyNameTable_[KEY_INPUT_D] = L"Ｄキー";
	keyNameTable_[KEY_INPUT_E] = L"Ｅキー";
	keyNameTable_[KEY_INPUT_F] = L"Ｆキー";
	keyNameTable_[KEY_INPUT_G] = L"Ｇキー";
	keyNameTable_[KEY_INPUT_H] = L"Ｈキー";
	keyNameTable_[KEY_INPUT_I] = L"Ｉキー";
	keyNameTable_[KEY_INPUT_J] = L"Ｊキー";
	keyNameTable_[KEY_INPUT_K] = L"Ｋキー";
	keyNameTable_[KEY_INPUT_L] = L"Ｌキー";
	keyNameTable_[KEY_INPUT_M] = L"Ｍキー";
	keyNameTable_[KEY_INPUT_N] = L"Ｎキー";
	keyNameTable_[KEY_INPUT_O] = L"Ｏキー";
	keyNameTable_[KEY_INPUT_P] = L"Ｐキー";
	keyNameTable_[KEY_INPUT_Q] = L"Ｑキー";
	keyNameTable_[KEY_INPUT_R] = L"Ｒキー";
	keyNameTable_[KEY_INPUT_S] = L"Ｓキー";
	keyNameTable_[KEY_INPUT_T] = L"Ｔキー";
	keyNameTable_[KEY_INPUT_U] = L"Ｕキー";
	keyNameTable_[KEY_INPUT_V] = L"Ｖキー";
	keyNameTable_[KEY_INPUT_W] = L"Ｗキー";
	keyNameTable_[KEY_INPUT_X] = L"Ｘキー";
	keyNameTable_[KEY_INPUT_Y] = L"Ｙキー";
	keyNameTable_[KEY_INPUT_Z] = L"Ｚキー";

	padNameTable_[PAD_INPUT_A] = L"Ａボタン";
	padNameTable_[PAD_INPUT_B] = L"Ｂボタン";
	padNameTable_[PAD_INPUT_C] = L"Xボタン";
	padNameTable_[PAD_INPUT_X] = L"Yボタン";
	padNameTable_[PAD_INPUT_Y] = L"Lボタン";
	padNameTable_[PAD_INPUT_Z] = L"Rボタン";
	padNameTable_[PAD_INPUT_L] = L"SELECTボタン";
	padNameTable_[PAD_INPUT_R] = L"STARTボタン";
	padNameTable_[PAD_INPUT_START] = L"左レバー押込";
	padNameTable_[PAD_INPUT_M] = L"右レバー押込";

	menuList_ = { L"Save&Exit KeyConfig",L"Cancel&Exit KeyConfig",L"Reset Input Data" };
	menuFuncs_[L"Save&Exit KeyConfig"] = [this](Input&)
		{
			input_.inputTable_ = input_.tempInputTable_;
			update_ = &KeyConfigScene::DisappearUpdate;
			draw_ = &KeyConfigScene::IntervalDraw;
		};
	menuFuncs_[L"Cancel&Exit KeyConfig"] = [this](Input&)
		{
			update_ = &KeyConfigScene::DisappearUpdate;
			draw_ = &KeyConfigScene::IntervalDraw;
		};
	menuFuncs_[L"Reset Input Data"] = [this](Input&)
		{
		};
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
	const int menuRowSize = input.editableEventNames_.size() + menuList_.size();

	if (input.IsTriggerd("ok"))
	{
		//これは「最後の行」なので、Exitである
		//なので、ここでokが押されたらもう閉じる状態に移行する
		if (selectIndex_ >= input_.editableEventNames_.size())
		{
			auto menuIndex = selectIndex_ - input_.editableEventNames_.size();
			auto menuName = menuList_[menuIndex];
			menuFuncs_[menuName](input);
			return;
			//if (selectIndex_ == input_.editableEventNames_.size())//Save&Exit
			//{
			//	update_ = &KeyConfigScene::DisappearUpdate;
			//	draw_ = &KeyConfigScene::IntervalDraw;
			//	input_.inputTable_ = input_.tempInputTable_;
			//	frame_ = appear_interval;
			//	return;
			//}
			//if (selectIndex_ == input_.editableEventNames_.size() + 1)//Cancel&Exit
			//{
			//	update_ = &KeyConfigScene::DisappearUpdate;
			//	draw_ = &KeyConfigScene::IntervalDraw;
			//	frame_ = appear_interval;
			//	return;
			//}
		}
		else
		{
			//もし、イベント名のところでokが押されていたら
		//エディットモードに切り替える
			update_ = &KeyConfigScene::EditingUpdate;
			draw_ = &KeyConfigScene::EditingDraw;
			isFirstEditFrame_ = true;
			return;
		}
	}
	
	if (input.IsTriggerd("up"))
	{
		selectIndex_ = (selectIndex_ + menuRowSize - 1) % menuRowSize;
	}
	if (input.IsTriggerd("down"))
	{
		selectIndex_ = (selectIndex_ + 1) % menuRowSize;
	}
}

void KeyConfigScene::DisappearUpdate(Input&)
{
	if (--frame_ <= 0)
	{
		controller_.PopScene();
	}
}

void KeyConfigScene::EditingUpdate(Input& input)
{
	if (input.IsTriggerd("ok"))
	{
		update_ = &KeyConfigScene::NormalUpdate;
		draw_ = &KeyConfigScene::NormalDraw;
		isFirstEditFrame_ = false;
		return;
	}
	lastKeyState_ = currentKeyState_;
	lastPadState_ = currentPadState_;
	//生入力を取得します
	GetHitKeyStateAll(currentKeyState_.data());
	currentPadState_ = GetJoypadInputState(DX_INPUT_PAD1);
	if (isFirstEditFrame_)
	{
		isFirstEditFrame_ = false;
		return;
	}
	auto eventName = input_.editableEventNames_[selectIndex_];
	//何かが入力されていたらそれを使用する
	//キーボードの入力をチェックする
	for (int keycode = 0; keycode < currentKeyState_.size(); ++keycode)
	{
		if (!keyNameTable_.contains(keycode)) continue;
		if (currentKeyState_[keycode] && !lastKeyState_[keycode])
		{
			//最初にtrueのものを見つけたらそれをキーコードとする
			for (auto& inputRow : input.tempInputTable_[eventName])
			{
				if (inputRow.type == PeripheralType::keyboard)
				{
					inputRow.id = keycode;
				}
			}
			break;
		}
	}
	//パッド入力をチェック
	uint32_t bit = 0b1;
	for (int i = 0; i < 32; ++i)
	{
		if (!padNameTable_.contains(bit))
		{
			bit <<= 1;//continueの際でもbitは進めないと止まってしまう
			continue;
		}

		if ((currentPadState_ & bit) && !(lastPadState_&bit))
		{
			for (auto& inputRow : input.tempInputTable_[eventName])
			{
				if (inputRow.type == PeripheralType::pad1)
				{
					inputRow.id = bit;
				}
			}
			break;
		}
		bit <<= 1;
	}
}

void KeyConfigScene::IntervalDraw()
{
	float rate = static_cast<float>(frame_) / static_cast<float>(appear_interval);
	auto frameSize = MaxFrameSize();
	DrawFrame(frameSize.w / 2, frameSize.h / 2,
		(frameSize.w / 2) * rate, frameSize.h / 2);
}

void KeyConfigScene::DrawFrame(int centerX, int CenterY, int w, int h)
{
	//キーコンフィグの背景
	DrawBox(
		centerX - w,
		CenterY - h,
		centerX + w,
		CenterY + h,
		0x44aa44, true);

	//キーコンフィグの外枠
	DrawBox(
		centerX - w,
		CenterY - h,
		centerX + w,
		CenterY + h,
		0xffffff, false, 3);
}

Size KeyConfigScene::MaxFrameSize() const
{
	constexpr int frame_margin = 20;//画面端からの余白
	const auto& wsize = Application::GetInstance().GetWindowSize();
	return { wsize.w - frame_margin,wsize.h - frame_margin };
}

void KeyConfigScene::NormalDraw()
{
	const auto& wsize = Application::GetInstance().GetWindowSize();
	const auto frameSize = MaxFrameSize();
	const auto centerX = wsize.w / 2;
	const auto centerY = wsize.h / 2;
	const auto frameW = frameSize.w / 2;
	const auto frameH = frameSize.h / 2;

	//枠表示
	DrawFrame(centerX, centerY, frameW, frameH);

	std::map<PeripheralType, std::wstring> periNameTable;
	periNameTable[PeripheralType::keyboard] = L"キーボード";
	periNameTable[PeripheralType::pad1] = L"パッド";


	//キーコンフィグのテキスト
	int y = centerY - frameH;
	//ここ以降でy+=?と書いている部分は、少しずつyを下に下げていきつつ
	//文字列を表示するため
	y += 10;
	//キーコンフィグタイトル
	DrawString(centerX - 50, centerY - frameH + 10, L"KeyConfig", 0xffffff);
	y += 100;
	bool isSelectedEvent = false;
	//イベント名と、実際に割り当てられているボタンを表示します
	for (const auto& name : input_.editableEventNames_)
	{
		int x = centerX - frameW + menu_left_margin;
		if (selectIndex_ < input_.editableEventNames_.size())
		{
			if (input_.editableEventNames_[selectIndex_] == name)
			{
				DrawString(x - 20, y, L"⇒", 0xff0000);
				isSelectedEvent = true;
				x += 10;
			}
		}
		
		//イベント名を表示
		auto wname = StringFunctions::WStringFromString(name);
		DrawFormatString(x, y, 0xffffff, L"%s", wname.c_str());
		//右にちょっとずらして、実際の入力コードを表示
		x += 50;
		
		for (const auto& inputState : input_.tempInputTable_[name])
		{
			DrawFormatString(x, y, 0xffffff, L"%s : %s", 
				periNameTable[inputState.type].c_str(),
				inputState.type == PeripheralType::keyboard ? //三項演算子
					keyNameTable_[inputState.id].c_str() :
					padNameTable_[inputState.id].c_str());
			x += 250;
		}
		y += 30;
	}
	//イベントの行と少し離しておく
	y += 50;

	for (const auto name : menuList_)
	{
		auto x = centerX - frameW + menu_left_margin + 150;
		if (selectIndex_ >= input_.editableEventNames_.size())
		{
			if (menuList_[selectIndex_ - input_.editableEventNames_.size()] == name)
			{
				DrawString(x - 20, y, L"⇒", 0xff0000);
				x += 10;
			}
		}
		DrawFormatString(x, y, 0xffffff, L"%s", name.c_str());

		x = centerX - frameW + menu_left_margin + 150;
		y += 30;
	}
}

void KeyConfigScene::EditingDraw()
{
	const auto& wsize = Application::GetInstance().GetWindowSize();
	const auto frameSize = MaxFrameSize();
	const auto centerX = wsize.w / 2;
	const auto centerY = wsize.h / 2;
	const auto frameW = frameSize.w / 2;
	const auto frameH = frameSize.h / 2;

	//枠表示
	DrawFrame(centerX, centerY, frameW, frameH);

	std::map<PeripheralType, std::wstring> periNameTable;
	periNameTable[PeripheralType::keyboard] = L"キーボード";
	periNameTable[PeripheralType::pad1] = L"パッド";


	//キーコンフィグのテキスト
	int y = centerY - frameH;
	//ここ以降でy+=?と書いている部分は、少しずつyを下に下げていきつつ
	//文字列を表示するため
	y += 10;
	//キーコンフィグタイトル
	DrawString(centerX - 50, centerY - frameH + 10, L"KeyConfig", 0xffffff);
	y += 100;
	//イベント名と、実際に割り当てられているボタンを表示します
	for (const auto& name : input_.editableEventNames_)
	{
		//編集中状態で、もし現在編集中の行を選択していれば
		//選択中の行の色を変更し、もうちょっとだけ右にずらす
		int x = centerX - frameW + menu_left_margin;
		uint32_t col = 0xffffff;//ちょっと右にずらす
		if (input_.editableEventNames_[selectIndex_] == name)
		{
			x += 10;
			DrawString(x - 20, y, L"⇒", 0xff0000);
			col = 0xaa00ff;//行の色を変更
			x += 10;
		}
		//イベント名を表示
		auto wname = StringFunctions::WStringFromString(name);
		DrawFormatString(x, y, col, L"%s", wname.c_str());
		//右にちょっとずらして、実際の入力コードを表示
		x += 50;

		for (const auto& inputState : input_.tempInputTable_[name])
		{
			DrawFormatString(x, y, col, L"%s : %s",
				periNameTable[inputState.type].c_str(),
				inputState.type == PeripheralType::keyboard ? //三項演算子
				keyNameTable_[inputState.id].c_str() :
				padNameTable_[inputState.id].c_str());
			x += 250;
		}
		y += 30;
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
