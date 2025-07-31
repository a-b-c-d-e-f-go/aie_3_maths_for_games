#pragma once
#include "SceneParent.h"
#include "SceneChild.h"

using namespace std;
using namespace BaseClasses;
using namespace MathClasses;

namespace BaseClasses
{
	class SceneObject : public SceneParent, public SceneChild
	{
	protected:
		SceneObject* parent = nullptr; //Stored as a SceneObject* because that has transform. If it is a root object, the parent will be nullptr.
		list<SceneChild*>* root_objects = nullptr; //A pointer to a list of pointers. This allows access to the game's children, letting them create new root objects.
		Matrix2H local_transform = Matrix2H::MakeIdentity(); //Unaffected by parents. Changed by functions.
		Matrix2H global_transform = Matrix2H::MakeIdentity(); //Updated every frame the local transform is changed.
		void UpdateGlobalTransform()
		{
			if (parent == nullptr) //Without a parent, global transform and local transform are the same.
			{
				global_transform = local_transform;
			}
			else //Otherwise, concatenate the matricies.
			{
				global_transform = parent->global_transform * local_transform;
			}
			global_transform_dirty = false;
			for (auto& i : children) { //When updating global transform, make sure all the children do as well.
				i->global_transform_dirty = true;
			}
		}
	public:
		//Constructors/Destructors
		SceneObject(list<SceneChild*>* _root = nullptr, float _x = 0, float _y = 0)
		{
			construct_object();
		}
		virtual ~SceneObject() override
		{
			cout << "      Deleting SceneObject - ";
			clear_children();
			parent = nullptr;
		}
		//Frame Update
		virtual void Update(float delta_time) override sealed //Not to be confused with OnUpdate(), which can be overridden. This function does the things all SceneObjects do every frame, including OnUpdate().
		{
			OnUpdate(delta_time);
			if (global_transform_dirty)
			{
				UpdateGlobalTransform();
			}
			for (auto& i : children) { //Loop through children to update them.
				i->Update(delta_time);
			}
			children.remove_if(deletion_pass); //Loop through children to delete any that should be deleted.
		}
		virtual void Draw() override sealed //Not to be confused with OnDraw(), which can be overridden. This function does the things all SceneObjects do every draw frame, including OnDraw().
		{
			OnDraw();
			for (auto& i : children) { //Loop through children to draw them.
				i->Draw();
			}
		}

		//Hierarchy
		void AddChild(SceneObject* _child)
		{
			(_child->parent) = this;
			children.push_back(_child);
		}
		void RemoveChild(SceneObject* _child)
		{
			_child->parent = nullptr;
			children.remove(_child);
		}
		bool operator==(const SceneObject& _other) const
		{
			return (parent == _other.parent) && (children == _other.children);
		}

		//Virtual
		virtual void OnUpdate(float delta_time) abstract {}
		virtual void OnDraw() abstract {}

		//Matricies
		virtual void SetPosition(float _x, float _y) override sealed
		{
			local_transform.Tx = _x;
			local_transform.Ty = _y;
			global_transform_dirty = true;
		}
		virtual void Translate(float _x, float _y) override sealed
		{
			local_transform *= Matrix2H::MakeTranslation(_x, _y);
			global_transform_dirty = true;
		}
		virtual void Rotate(float _r) override sealed
		{
			local_transform *= Matrix2H::MakeRotation(_r);
			global_transform_dirty = true;
		}
		virtual void Scale(float _x, float _y) override sealed
		{
			local_transform *= Matrix2H::MakeScale(_x, _y);
			global_transform_dirty = true;
		}
	};
}