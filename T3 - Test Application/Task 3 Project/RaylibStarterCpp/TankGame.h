#pragma once
#include "Defines.h"
#include "Tank.h"
#include "Wall.h"

using namespace std;
using namespace BaseClasses;
using namespace TankClasses;

namespace TankClasses
{
	class TankGame : public Game
	{
	public:
		void Init() override
		{
			//Layering is decided by who is spawned in first. The player is spawned last so that they are more visible.

			//Horizontal Wall
			SceneChild* o = new Wall(&children, GetScreenWidth() - 100, GetScreenHeight() / 2.0f, 32, GetScreenHeight() * 0.6f);
			children.push_back(o);

			//Vertical Wall
			o = new Wall(&children, GetScreenWidth() / 2.0f, 100, GetScreenWidth() * 0.6f, 32);
			children.push_back(o);

			//Tank
			o = new Tank(&children);
			o->Scale(2, 2);
			o->SetPosition(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f);
			children.push_back(o);
		}
	};
}