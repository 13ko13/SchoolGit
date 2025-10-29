#include "Input.h"
#include <DxLib.h>

Input::Input() :
	inputData_{},
	lastInputData_{},
	inputTable_{}
{
	//イベント名を添え字にして、右辺値に実際の入力種別と入力コードの配列を置く
	inputTable_["ok"] = { { PeripheralType::keyboard, KEY_INPUT_RETURN },
							{  PeripheralType::pad1,PAD_INPUT_L } };//SELECTキー
	inputTable_["pause"] = { { PeripheralType::keyboard, KEY_INPUT_P },
							{  PeripheralType::pad1,PAD_INPUT_R } };
	inputTable_["shot"] = { { PeripheralType::keyboard, KEY_INPUT_Z },
							{PeripheralType::pad1, PAD_INPUT_C } };//PADのXボタン
	inputTable_["up"] = { { PeripheralType::keyboard, KEY_INPUT_UP },
							{PeripheralType::pad1,PAD_INPUT_UP } };
	inputTable_["down"] = { { PeripheralType::keyboard, KEY_INPUT_DOWN },
							{PeripheralType::pad1,PAD_INPUT_DOWN } };
	inputTable_["left"] = { { PeripheralType::keyboard, KEY_INPUT_LEFT },
		{PeripheralType::pad1,PAD_INPUT_LEFT } };
	inputTable_["right"] = { { PeripheralType::keyboard, KEY_INPUT_RIGHT },
							{PeripheralType::pad1,PAD_INPUT_RIGHT } };

	//あらかじめ入力データのための枠を開けておく
	//ここで枠を開けておかないと、チェックの際にAt関数でクラッシュする可能性がある
	for (const auto& inputInfo : inputTable_)
	{
		inputData_[inputInfo.first] = false;
		lastInputData_[inputInfo.first] = false;
	}
}

void Input::Update()
{
	//まず現在の入力情報を取得
	char keyState[256];
	GetHitKeyStateAll(keyState);//生のキーボード情報
	int padState = GetJoypadInputState(DX_INPUT_PAD1);//生のPAD1情報
	lastInputData_ = inputData_;//直前のフレームを更新(前のフレーム情報をコピー)
	//すべての入力イベントをチェックします
	//ここでinputData_が更新される
	//inputTable_を回して各イベントの入力をチェックする
	for (const auto& inputInfo : inputTable_)
	{
		auto& input = inputData_[inputInfo.first];//inputInfo.firstには"ok"等がはいってる
		//inputを書き換えると、inputData_のそのイベントが押されてるかどうかを
		//書き換えることになる
		for (const auto& state : inputInfo.second){//InputStateのベクタを回す
			//子のループはInputState配列のループなので
			//まず、入力種別をチェックします　
			switch (state.type)
			{
			case PeripheralType::keyboard://キーボードだったら
				//GetHitKeyStateAllでとってきた配列の中身を見て
				//入力されているか同課をチェック
				input = keyState[state.id];
				break;
			case PeripheralType::pad1:
				//GetJoypadStatedでとってきたビット情報を見て
				//登録されてるビット情報と&を取り、そのビットが立っているかどうかをチェック
				input = (padState & state.id);
				break;
			}
			if (input)	//大事！必須!
			{
				//breakしないとpad1がそのままのこってしまう
				//最後のチェックで押されてないとfalseになってしまう
				break;
			}
		}
	}
}

bool Input::IsPressed(const char* name) const
{
	//もし「ない」イベントを送られるとクラッシュします
	//もしクラッシュがいやだったら
	//if (inputData_.contains(name)){
	//	return false;//で回避できます。
	//}
	return inputData_.at(name);//const関数内部なので[]ではなくatを使用してる
}

bool Input::IsTriggerd(const char* name) const
{
	return inputData_.at(name) && !lastInputData_.at(name);
}
