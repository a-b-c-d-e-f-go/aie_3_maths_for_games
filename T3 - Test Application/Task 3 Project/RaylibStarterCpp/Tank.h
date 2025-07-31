#pragma once
#include "Turret.h"
#include "Defines.h"

using namespace BaseClasses;
using namespace TankClasses;

namespace TankClasses
{
	class Tank : public SpriteObject
	{
	public:
		Tank(list<SceneChild*>* _root = nullptr, float _x = 0, float _y = 0)
		{
			construct_object();
			Load("../Images/TankBody.png");

			//Create Turret
			Turret* turret = new Turret(_root);
			AddChild(turret);
		}
		virtual ~Tank() override
		{
			cout << "  Deleting Tank\n";
		}
		virtual void OnUpdate(float delta_time) override
		{
			//Movement (Turn/Fire Turret is stored in the Turret)
			opposing_controls(turn, KEY_D, KEY_A);
			Rotate(turn / 36.0f * delta_time);

			opposing_controls(move, KEY_S, KEY_W);
			Translate(0, move / 2.0f * delta_time);
		}
	};
}