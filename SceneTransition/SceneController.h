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
	//���݃X�^�b�N�ɐς܂�Ă���V�[��
	//�Ō�ɐς񂾂��̂�����Update�����
	std::list<std::shared_ptr<Scene>> scenes_;
public:
	/// <summary>
	/// �V�[���̐؂�ւ�(�������A�����œn���ꂽ�V�[���݂̂ɂȂ�
	/// </summary>
	/// <param name="scene">�V�����V�[��</param>
	/// <note>�����œn���ꂽ�V�[���݂̂ɂȂ�A�ς܂�Ă�V�[���̐��͂P�ɂȂ�</note>
	void ResetScene(std::shared_ptr<Scene> scene);

	/// <summary>
	/// �V�[���̐؂�ւ�
	/// </summary>
	/// <param name="scene">�V�����V�[��</param>
	/// <note>�Ō�ɐς񂾃V�[����Change�����</note>
	void ChangeScene(std::shared_ptr<Scene> scene);

	/// <summary>
	/// �V�[����V�����ς݂܂�
	/// </summary>
	/// <param name="scene">�ς݂����V�[��</param>
	/// <note>ChangeScene�ƈ���āA���Ƃ��Ɛς܂�Ă�V�[���͎c�葱����</note>
	void PushScene(std::shared_ptr<Scene> scene);

	/// <summary>
	/// �Ō�ɐς񂾃V�[�������X�g����O��(�����I�ɉ�������)
	/// </summary>
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

