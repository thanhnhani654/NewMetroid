#include "SceneActor.h"

SceneActor* SceneActor::inst;

SceneActor* SceneActor::getInstance()
{
	if (inst == nullptr)
		inst = new SceneActor();
	return inst;
}

bool SceneActor::IsPause()
{
	return pause;
}

void SceneActor::PauseFor(float time)
{
	timePause = time;
	pause = true;
}

void SceneActor::TimeCount(float deltatime)
{
	if (pause)
	{
		if (timePause < 0)
			pause = false;
		timePause -= deltatime;
	}
}