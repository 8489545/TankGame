#include"stdafx.h"
#include"MainScene.h"
#include"IntroScene.h"
#include"StageSelect.h"
INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
#if _DEBUG
	AllocConsole();
	FILE* stream;
	freopen_s(&stream, "CONOUT$", "wt", stdout);

#endif
	App::GetInst()->Init(1920, 1080, 1);
	SceneDirector::GetInst()->ChangeScene(new IntroScene());
	App::GetInst()->Run();
	return 0;
}