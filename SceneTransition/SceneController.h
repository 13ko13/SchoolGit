#pragma once
#include <memory>
class Input;
class Scene;
/// <summary>
/// �V�[��������ɕێ����A�؂�ւ���񋟂���
/// </summary>
class SceneController
{
private:
	std::shared_ptr<Scene> scene_;//���ݎ��s���̃V�[��
public:
	/// <summary>
	/// �V�[���̐؂�ւ�
	/// </summary>
	/// <param name="scene">�V�����V�[��</param>
	void ChangeScene(std::shared_ptr<Scene> scene);
	/// <summary>
	/// �����Ɏ����Ă�V�[����Update���Ăяo��
	/// </summary>
	void Update(Input& input);
	/// <summary>
	/// �����Ɏ����Ă�V�[����Draw���Ăяo��
	/// </summary>
	void Draw();
};

