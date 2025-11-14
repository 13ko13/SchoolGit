#include "SceneController.h"
#include "../Scene.h"

void SceneController::ResetScene(std::shared_ptr<Scene> scene)
{
	//シーンを１つだけにしたいため、一旦シーンをすべてクリアします
	scenes_.clear();
	scenes_.push_back(scene);
}

void SceneController::ChangeScene(std::shared_ptr<Scene> scene)
{
	//もし、リストがカラの場合、普通に代入でChangeSceneしようとすると
	//当然emptyの箱に対してChangeしようとするので、クラッシュします
	//このため、最初にemptyかどうかをチェックします
	if (scenes_.empty())
	{
		//最初は要素がないため
		//空っぽの場合には指定の要素をpushします
		//少なくとも1つは積まれている状態にする
		scenes_.push_back(scene);
	}
	else
	{
		scenes_.back() = scene;
	}
}

void SceneController::PushScene(std::shared_ptr<Scene> scene)
{
	//新しいシーンを末尾に積みます(下から積む？)
	scenes_.push_back(scene);
}

void SceneController::PopScene()
{
	//末尾のシーンを削除します
	scenes_.pop_back();
}

void SceneController::Update(Input& input)
{
	//末尾の要素に対してUpdateする
	scenes_.back()->Update(input);
}

void SceneController::Draw()
{
	//Updateだけ止めてすべてDraw
	//ポーズしたときにプレイ背景は残る
	for (auto& scene : scenes_)
	{
		scene->Draw();
	}
}