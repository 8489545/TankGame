#pragma once
class SceneDirector : public Singleton<SceneDirector>
{
	Object* m_CurrentScene;

public:
	SceneDirector();
	~SceneDirector();

	void ChangeScene(Object* newScene);

	void Update(float deltaTime,float time);
	void Render();

};

