#pragma once
#include "Scene.h"
class KeyConfigScene : public Scene
{
private:
	Input& input_;
	int frame_;

	using UpdateFunc_t = void(KeyConfigScene::*)(Input&);
	UpdateFunc_t update_;

	using DrawFunc_t = void(KeyConfigScene::*)();
	DrawFunc_t draw_;

	//UpdateèÛë‘ä÷êî
	void AppearUpdate(Input&);
	void NormalUpdate(Input&);
	void DisappearUpdate(Input&);

	//DrawånèÛë‘ä÷êî
	void NormalDraw();
	void IntervalDraw();

public:
	KeyConfigScene(SceneController&ctrl,Input& input);

	void Update(Input& input) override;
	void Draw() override;
};

