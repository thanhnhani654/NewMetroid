#pragma once


// Đây là class có chức năng điều khiển hoạt động của scene như pause scene, etc

class SceneActor
{
private:
	bool pause;
	float timePause;
	static SceneActor* inst;

public:
	static SceneActor* getInstance();
	bool IsPause();
	void PauseFor(float time);
	void TimeCount(float time);
};