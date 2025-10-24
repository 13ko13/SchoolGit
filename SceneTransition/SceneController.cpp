#include "SceneController.h"
#include "Scene.h"

void SceneController::ChangeScene(std::shared_ptr<Scene> scene)
{
	//scene代入された際に、元々別のシーンがscene_に入っていたら
	//もともとのscene_の参照先を参照するオブジェクトがいなくなるため
	// もとのscene_は自動的に削除されます
	if (scenes_.empty())
	{
		scenes_.push_back(scene);
	}
	else
	{
		scenes_.back() = scene;
	}
}

void SceneController::PushScene(std::shared_ptr<Scene> scene)
{
}

void SceneController::PopScene()
{
}

void SceneController::Update(Input& input)
{
	scenes_.back()->Update(input);
}

void SceneController::Draw()
{
	scenes_.back()->Draw();
}