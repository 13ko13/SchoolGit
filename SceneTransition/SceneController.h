#pragma once
#include <memory>
class Input;
class Scene;
/// <summary>
/// シーンを内部に保持し、切り替えを提供する
/// </summary>
class SceneController
{
private:
	std::shared_ptr<Scene> scene_;//現在実行中のシーン
public:
	/// <summary>
	/// シーンの切り替え
	/// </summary>
	/// <param name="scene">新しいシーン</param>
	void ChangeScene(std::shared_ptr<Scene> scene);
	/// <summary>
	/// 内部に持ってるシーンのUpdateを呼び出す
	/// </summary>
	void Update(Input& input);
	/// <summary>
	/// 内部に持ってるシーンのDrawを呼び出す
	/// </summary>
	void Draw();
};

