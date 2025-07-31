#pragma once
#include "SceneParent.h"

using namespace std;
using namespace BaseClasses;
using namespace MathClasses;

namespace BaseClasses
{
	class Game : public SceneParent
	{
	protected:
		float delta_time = 0;
	public:
		Game()
		{

		}
		~Game()
		{
			//Log cleanup process in the console.
			std::cout << "\n          --CLEANUP START--\n";
			clear_children();
			std::cout << "          --CLEANUP END--\n";
		}
		virtual void Init()
		{
		}
		void Update()
		{
			delta_time = GetFrameTime() * 60; //Target framerate is 60FPS.
			for (auto& i : children) { //Loop through children to update them.
				i->Update(delta_time);
			}
			children.remove_if(deletion_pass); //Loop through children to delete any that should be deleted.
		}
		void Draw()
		{
			BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawText(to_string(GetFPS()).c_str(), 20, 20, 30, BLACK); //FPS Counter
			for (auto& i : children) { //Loop through children to draw them.
				i->Draw();
			}
			EndDrawing();
		}
	};
}