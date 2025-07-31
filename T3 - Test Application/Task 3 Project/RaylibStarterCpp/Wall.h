#pragma once
#include "Defines.h"

using namespace BaseClasses;

namespace TankClasses
{
	class Wall : public SpriteObject
	{
	public:
		Wall(list<SceneChild*>* _root = nullptr, float _x = 0, float _y = 0, float _width = 32, float _height = 32)
		{
			Scale(_width, _height);
			construct_object();
			Load("../Images/Wall.png");
		}
		virtual ~Wall() override
		{
			cout << "  Deleting Wall\n";
		}
		virtual void OnUpdate(float delta_time) override
		{

		}
		bool WithinBounds(float _x, float _y) //Check if a point intersects with the box. Will not work properly with rotated walls.
		{
			float hwidth = img.width * abs(global_transform.Xx) / 2; //Half-Width
			float hheight = img.height * abs(global_transform.Yy) / 2; //Half-Height

			bool within_x_range = (_x < global_transform.Tx + hwidth && _x > global_transform.Tx - hwidth);
			bool within_y_range = (_y < global_transform.Ty + hheight && _y > global_transform.Ty - hheight);
			return within_x_range && within_y_range;
		}
	};
}