#pragma once

typedef struct D3DXVECTOR2 Vec2;
typedef struct D3DXMATRIX Matrix;

#define dt App::GetInst()->DeltaTime
#define gt App::GetInst()->Time
#define _USE_MATH_DEFINES

using namespace std;

template<class T>
inline void SafeDelete(T*& x);

#include<Windows.h>
#include<stdio.h>
#include<iostream>
#include<d3d9.h>
#include<d3dx9.h>
#include<dsound.h>
#include<map>
#include<list>
#include<ctime>
#include<vector>
#include<string>
#include<sstream>
#include<cmath>
//
#include"Singleton.h"
#include"Input.h"
#include"Renderer.h"
#include"App.h"
#include"Object.h"
#include"ObjectMgr.h"
#include"CollisionMgr.h"
#include"SceneDirector.h"
#include"TextMgr.h"
#include"SoundMgr.h"
#include"LineMgr.h"
#include"Camera.h"
#include"Sprite.h"
#include"Animation.h"
#include"CannonMgr.h"
#include"GameMgr.h"
#include"TileMgr.h"
#include"Player.h"

//

template<class T>
inline void SafeDelete(T*& x)
{
	delete x;
	x = static_cast<T*>(0);
};