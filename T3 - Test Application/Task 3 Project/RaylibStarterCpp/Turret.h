#pragma once
#include "Defines.h"
#include "Bullet.h"

using namespace BaseClasses;

namespace TankClasses
{
	class Turret : public SpriteObject
	{
	public:
		Turret(list<SceneChild*>* _root = nullptr, float _x = 0, float _y = 0)
		{
			construct_object();
			Load("../Images/TankGun.png");
			
		}
		virtual ~Turret() override
		{
			cout << "  Deleting Turret\n";
		}
		virtual void OnUpdate(float delta_time) override
		{
			//Rotate Turret
			opposing_controls(turn, KEY_E, KEY_Q);
			Rotate(turn / 16.0f * delta_time);

			//Fire Turret
			if (IsKeyPressed(KEY_SPACE))
			{
				//Attach New Bullet to Root Objects
				Bullet* b = new Bullet(root_objects);
				root_objects->push_back((SceneChild*)b);

				//Apply Transforms
				b->Scale(2.0f, 2.0f); //Scale to 2x.
				b->Rotate(atan2(global_transform.Xy, global_transform.Xx) + PI); //Rotate to face in the direction of the turret.
				b->SetPosition(global_transform.Tx - (global_transform.Yx * 10.0f), global_transform.Ty - (global_transform.Yy * 10.0f)); //Spawn the bullet at the turret, offset by 10x the y-axis (about the length of the turret).
			}
		}
	};
}