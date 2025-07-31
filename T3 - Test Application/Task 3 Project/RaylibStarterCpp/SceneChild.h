#pragma once
#include "SceneParent.h"

//This interface exists purely to be accessed by SceneParent, since it is a superclass of Game and SceneObject and cannot access those 2 classes.
namespace BaseClasses
{
	class SceneChild
	{
	public:
		bool global_transform_dirty = true;
		bool should_delete = false;
		virtual void Update(float delta_time) abstract;
		virtual void Draw() abstract;
		virtual void SetPosition(float _x, float _y) abstract;
		virtual void Translate(float _x, float _y) abstract;
		virtual void Rotate(float _r) abstract;
		virtual void Scale(float _x, float _y) abstract;
		virtual ~SceneChild() {}
	};
}