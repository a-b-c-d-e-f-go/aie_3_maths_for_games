#pragma once
#include "SceneObject.h"

#include "stdio.h"
#include <list>

using namespace BaseClasses;
using namespace MathClasses;

namespace BaseClasses
{
	class SpriteObject : public SceneObject
	{
	protected:
		Texture2D img = Texture2D();
	public:
		//Constructors/Destructors
		using SceneObject::SceneObject; //Inherit Constructors
		virtual ~SpriteObject() override //All these constructors play in sequence, so a Tank would use ~Tank, then ~SpriteObject, then ~SceneObject when getting deleted.
		{
			cout << "    Deleting SpriteObject - ";
			UnloadTexture(img);
		}

		void Load(const char* fileName)
		{
			img = LoadTexture(fileName);
		}
		virtual void OnUpdate(float delta_time)
		{

		}
		virtual void OnDraw() override
		{
			//This defeats the whole point of using matricies here, since we're converting rotation/scale into (Xx, Xy, Yx, Yy), then converting them back so we can use raylib's DrawTexturePro.
			float rotation = atan2(global_transform.Xy, global_transform.Xx);
			float width = img.width * global_transform.Xx / cosf(rotation);
			float height = img.height * global_transform.Yy / cosf(rotation);

			//Making the rectangles and vectors for DrawTexturePro.
			Rectangle source = { 0.0f, 0.0f, img.width, img.height }; //The part of the texture file we want to use.
			Rectangle dest = Rectangle{ global_transform.Tx, global_transform.Ty, width, height }; //Where the texture is drawn to (including scale).
			Vector2 origin = Vector2{ width / 2.0f, height / 2.0f }; //The origin (center) of the texture.

			DrawTexturePro(img, source, dest, origin, rotation * (180 / PI), WHITE); //Draw the texture.
		}
	};
}



		/*void rlSetTexture(unsigned int id) {}
		RLAPI void DrawTextureMat(Texture2D& texture, Rectangle source, Matrix2H& mat)
		{
			rlSetTexture(texture.id);
			rlBegin(RL_QUADS);

			rlColor4ub(WHITE.r, WHITE.g, WHITE.b, WHITE.a);
			rlNormal3f(0.0f, 0.0f, 1.0f); //Normal vector pointing towards viewer


			// Top-left corner for texture and quad
			rlTexCoord2f((source.x + source.width) / texture.width, source.y / texture.height);
			rlVertex2f(mat.Yx, mat.Yy);

			// Bottom-left corner for texture and quad
			rlTexCoord2f((source.x + source.width) / texture.width, (source.y + source.height) / texture.height);
			rlVertex2f(mat.Yx, mat.Xy);

			// Bottom-right corner for texture and quad
			rlTexCoord2f(source.x / texture.width, (source.y + source.height) / texture.height);
			rlVertex2f(mat.Xx, mat.Xy);

			// Top-right corner for texture and quad
			rlTexCoord2f(source.x / texture.width, source.y / texture.height);
			rlVertex2f(mat.Xx, mat.Yy);

			rlEnd();
			rlSetTexture(0);
		}*/