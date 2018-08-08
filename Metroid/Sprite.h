#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <Windows.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "pugixml-1.8\src\pugixml.hpp"
#include <string>
#include "GameObject\Camera.h"

using namespace std;

struct SpritePos
{
	string id;
	float x;
	float y;
	float w;
	float h;
};

struct AnimationClip
{
	string name;
	LPDIRECT3DTEXTURE9 image;
	int clipCount;
	SpritePos Clip[10];
	AnimationClip()
	{
		name = "null";
		image = nullptr;
		clipCount = 0;
		for (int i = 0; i < 10; i++)
		{
			Clip[i].id = "nullptr";
			Clip[i].h = 0;
			Clip[i].w = 0;
			Clip[i].x = 0;
			Clip[i].y = 0;
		}
	}
};

class Sprite
{
protected:
	static LPDIRECT3DTEXTURE9 _Image;
	static LPDIRECT3DTEXTURE9 _Image2;
	static LPDIRECT3DTEXTURE9 _Image3;
	static LPDIRECT3DTEXTURE9 _Image4;
	static LPDIRECT3DTEXTURE9 _Image5;
	
	static LPD3DXSPRITE _SpriteHandler;
	static LPDIRECT3DDEVICE9 d3ddv;	

	static vector <SpritePos> spritepos;
	
	LPDIRECT3DTEXTURE9 _MainImage;
	AnimationClip currentAnim;
	SpritePos* currentSprite;
	int index;
	int frameRate;							//Điều chỉnh tốc độ chuyển hình theo tỉ lệ 1/1, 1/2, 1/3, 1/4 ... tương ứng với frameRate 1,2,3,4...
	int countFrame;
	bool _Flip;
public:


	static vector <AnimationClip> animClips;
	Sprite() {}
	static LPDIRECT3DTEXTURE9 LoadSprite(LPCWSTR Path, int Width, int Height);
	static void Initialize();

	static void GetDevice(LPDIRECT3DDEVICE9 d3ddv);

	void Render(float X, float Y);
	void Next();
	static void LoadSpritePos(char* path);
	static SpritePos FindSpriteById(string id);
	static void LoadAnimClips(char* path, LPDIRECT3DTEXTURE9 image);
	static AnimationClip FindAnimByName(string name);

	void SetAnimation(string name);
	void SetFrameRate(int fr);
	
	//Debug
	static void PrintSpritePos(int mode);			// mode{1(Group), 2(Sheet)}
	static void PrintAnimationClip(int mode);		// mode{1(Group), 2(Sheet)}
	void FlipLeft();
	void FlipRight();
	bool isFilpLeft();								// Left:True		Right: False
};