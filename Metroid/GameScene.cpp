#include "GameScene.h"

void GameScene::Initialize()
{
	samus.Initialize();
	samus.SetPosition(16*35, 100);

	item.Initialize(eItem::RocketItem);
	item.SetPosition(16 * 48, 16*3);
	//b->SetPosition(16 * 33, 100);

	/*for (int i = 0; i < 20; i++)
	{
		Tiles* newObject = new Tiles();
		newObject->Initialize("Tile_0");
		newObject->SetPosition(i * 16+30, 30);
		object.push_back(newObject);
	}
	for (int i = 0; i < 20; i++)
	{
		Tiles* newObject = new Tiles();
		newObject->Initialize("Tile_0");
		newObject->SetPosition(i * 16 + 30, 200);
		object.push_back(newObject);
	}
	for (int i = 0; i < 20; i++)
	{
		Tiles* newObject = new Tiles();
		newObject->Initialize("Tile_0");
		newObject->SetPosition(0+30, i*16);
		object.push_back(newObject);
	}
	for (int i = 0; i < 20; i++)
	{
		Tiles* newObject = new Tiles();
		newObject->Initialize("Tile_0");
		newObject->SetPosition(300+30, i*16);
		object.push_back(newObject);
	}*/
	MapLoader();
}

void GameScene::UpdateInput(float deltatime)
{
	samus.UpdateInput(deltatime);
	
}

void GameScene::Update(float deltatime)
{
	samus.Update(deltatime);
	Bullet::UpdateBullets(deltatime);
	Camera::getInstance()->Update(deltatime, samus.GetPosition());
	GameObject::DestroyProcess();
	Bullet::DestroyBullets();
}

void GameScene::Draw()
{
	samus.Draw();
	item.Draw();
	Bullet::DrawBullets();
	for (int i = 0; i < object.size(); i++)
	{
		object[i]->Draw();
	}
}

void GameScene::MapLoader()
{
	fstream map;
	map.open("Resources/map.txt", ios::in);

	if (map.fail())
	{
		MessageBox(NULL, TEXT("Map not found!"), TEXT("ERROR"), NULL);
		return;
	}

	int width = 160;
	int height = 15;

	int maps[15][160];

	for (int y = height - 1; y >= 0; y--)
	{
		for (int x = 0; x < width; x++)
		{
			map >> maps[y][x];
		}
	}

	map.close();

	for (int y = height - 1; y >= 0; y--)
	{
		for (int x = 0; x < width; x++)
		{
			int tempx = x;
			int tempy = y;
			switch (maps[y][x])
			{
			case 1:
				{
				Tiles* newObject = new Tiles();
				newObject->Initialize("Tile_0");
				newObject->SetPosition(x*16,y*16);
				object.push_back(newObject);
				}
				break;
			case 0:
				{
					
				}
				break;
			}
		}
	}
}