#pragma once
#include "Defines.h"
#include "Wall.h"

using namespace std;
using namespace BaseClasses;

namespace TankClasses
{
	class Bullet : public SpriteObject
	{
	public:
		Bullet(list<SceneChild*>* _root = nullptr, float _x = 0, float _y = 0)
		{
			construct_object();
			Load("../Images/TankBullet.png");
		}
		virtual ~Bullet() override
		{
			cout << "  Deleting Bullet\n";
		}
		virtual void OnUpdate(float delta_time) override
		{
			Translate(0, delta_time * 4.0f); //Travel forward twice as far as it should so that collision checks are made in advance.

			//Screen Edges
			if (global_transform.Tx < 0 || global_transform.Ty < 0 || global_transform.Tx > GetScreenWidth() || global_transform.Ty > GetScreenHeight())
			{
				should_delete = true;
			}
			//Walls
			for (auto& i : *root_objects) { //Iterate through the children of the TankGame. Will not check for walls with parents.
				Wall* wall = dynamic_cast<Wall*>(i); //Cast i to wall.
				if (wall == nullptr)
				{
					//Cast failed.
				}
				else
				{
					//Cast successful.
					if (wall->WithinBounds(local_transform.Tx, local_transform.Ty)) //This check assumes that the bullet is not parented, but means we don't have to prematurely update the global transform.
					{
						should_delete = true;
					}
				}
			}

			Translate(0, delta_time * -2.0f); //Travel backward after collision check, meaning it only moves (2.0f * delta_time) every frame.
		}
	};
}