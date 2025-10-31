#pragma once
#include "Scene.h"
class KeyConfigScene : public Scene
{
public:
	KeyConfigScene(SceneController&);

	void Update(Input& input) override;
	void Draw() override;
};

