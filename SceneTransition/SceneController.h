#pragma once
#include <memory>
#include <list>
class Input;
class Scene;
/// <summary>
/// �V�[��������ɕێ����A�؂�ւ���񋟂���
/// </summary>
class SceneController
{
private:
	std::list<std::shared_ptr<Scene>> scenes_;//���ݎ��s���̃V�[��
public:
	/// <summary>
	/// �V�[���̐؂�ւ�
	/// </summary>
	/// <param name="scene">�V�����V�[��</param>
	void ChangeScene(std::shared_ptr<Scene> scene);

	void PushScene(std::shared_ptr<Scene> scene);
	void PopScene();

	/// <summary>
	/// �����Ɏ����Ă�V�[����Update���Ăяo��
	/// </summary>
	void Update(Input& input);


	/// <summary>
	/// �����Ɏ����Ă�V�[����Draw���Ăяo��
	/// </summary>
	void Draw();
};

