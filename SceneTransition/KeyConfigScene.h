#pragma once
#include "Scene.h"
#include "Geometry.h"
#include <map>
#include <string>

/// <summary>
/// キーコンフィグシーン
/// </summary>
class KeyConfigScene : public Scene
{
private:
	int selectIndex_ = 0;//現在選択中のインデックス

	std::map<uint32_t, std::wstring> padNameTable_;//パッドのボタン名テーブル
	std::map<int, std::wstring> keyNameTable_;//キーボードのキー名テーブル

	//drawなどで使用するInputクラスオブジェクトへの参照
	Input& input_;
	//ウィンドを開くときのフレームカウント
	int frame_;

	using UpdateFunc_t = void(KeyConfigScene::*)(Input&);
	UpdateFunc_t update_;

	using DrawFunc_t = void(KeyConfigScene::*)();
	DrawFunc_t draw_;

	//Update状態関数
	void AppearUpdate(Input&);
	void NormalUpdate(Input&);
	void DisappearUpdate(Input&);

	//現在、キーの内容を編集中
	void EditingUpdate(Input&);

	//Draw系状態関数
	void NormalDraw();
	void EditingDraw();
	void IntervalDraw();

	/// <summary>
	/// キーコンフィグの枠を表示
	/// </summary>
	/// <param name="w">枠の幅</param>
	/// <param name="h">枠の高さ</param>
	void DrawFrame(int centerX,int centerY, int w, int h);
	/// <summary>
	/// 最大枠サイズを返す
	/// </summary>
	/// <returns>最大枠サイズ</returns>
	Size MaxFrameSize() const;

public:
	/// <summary>
	/// KeyConfigSceneコンストラクタ
	/// </summary>
	/// <param name="ctrl">シーンコントローラ</param>
	/// <param name="input">Inputオブジェクト</param>
	KeyConfigScene(SceneController&ctrl,Input& input);

	void Update(Input& input) override;
	void Draw() override;
};

