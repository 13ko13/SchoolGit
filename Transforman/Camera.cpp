#include "Camera.h"
#include <DxLib.h>
#include "Geometry.h"
#include "GameConstants.h"

constexpr float half_pi = 180.0f;

Camera::Camera()
{
	//奥行
	SetCameraNearFar(cameraNear, cameraFar);

	//視野角の設定
	float fovRadian = fovDegree * (DX_PI_F / half_pi);
	SetupCamera_Perspective(fovRadian);//ラジアンに変換して設定

	//ポジションとターゲットからカメラの回転とポジションを同時設定する
	//カメラの位置は(0,0,CameraZPos)、注視点は(0,0,0)
	Vector3 pos = { Graphic::screen_height / 2, Graphic::screen_height / 2, 0 };
	Vector3 target = { Graphic::screen_height / 2, Graphic::screen_height / 2, 0 };
	pos = Graphic::To3DPosition(pos);
	pos = { pos.x, pos.y, pos.z + CameraZPos };
	target = Graphic::To3DPosition(target);
}

Camera::~Camera()
{
}