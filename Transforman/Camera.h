#pragma once
class Camera
{
	public:
	Camera();
	~Camera();

	//2D→3D変換の時に歪みを抑えるために視野角を狭める
	constexpr static float fovDegree = 10.0f;//視野角

	//near,farはなるべく小さくする
	constexpr static float cameraNear = 50.0f;//カメラのnear
	constexpr static float cameraFar = 100.0f;//カメラのfar

	//カメラのZ位置を下げる
	constexpr static float CameraZPos = -51.5f;//Z位置
};


