#pragma once

//Libraries
#include <stdio.h>
#include <iostream>
#include <string>
#include <list>
#include <math.h>

//BaseClasses
#include "SceneChild.h"
#include "Matrix2.h"
#include "Matrix2H.h"
#include "Vector2D.h"
#include "Vector3D.h"

//Namespaces
using namespace std;
using namespace BaseClasses;
using namespace MathClasses;

namespace BaseClasses
{
	//This class exists because both SceneObject and Game have a list of children and affect them in the same ways.
	class SceneParent
	{
	protected:
		list<SceneChild*> children = {};
		static bool deletion_pass(SceneChild* o) //Checks if an object should be deleted. Returns true and deletes it if yes.
		{
			if (o->should_delete)
			{
				delete o; return true;
			}
			return false;
		}
		void clear_children() //Deletes all children - typically used during cleanup.
		{
			cout << "Clearing List of " << children.size() << " Children\n";
			while (!children.empty())
			{
				delete children.front();
				children.front() = nullptr;
				children.pop_front();
			}
		}
	};
}