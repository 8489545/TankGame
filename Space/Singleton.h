#pragma once

template<class T>
class Singleton
{
private:
	static T* m_Instance;

public:
	Singleton() {}
	~Singleton() {}

	static T* GetInst()
	{
		if (m_Instance == 0)
			m_Instance = new T();

		return m_Instance;
	}

};

template<class T>
T* Singleton<T>::m_Instance = 0;