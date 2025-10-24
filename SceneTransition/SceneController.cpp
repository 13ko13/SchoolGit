#include "SceneController.h"
#include "Scene.h"

void SceneController::ChangeScene(std::shared_ptr<Scene> scene)
{
	//scene代入された際に、元々別のシーンがscene_に入っていたら
	//もともとのscene_の参照先を参照するオブジェクトがいなくなるため
	// もとのscene_は自動的に削除されます
	scene_ = scene;
}

void SceneController::Update(Input& input)
{
	scene_->Update(input);
}

void SceneController::Draw()
{
	scene_->Draw();
}