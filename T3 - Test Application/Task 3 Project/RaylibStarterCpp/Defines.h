#pragma once

//Macros
#define delete_list(l) cout << "Clearing List of " << l.size() << " Children\n"; while (!l.empty()) { delete l.front(); l.front() = nullptr; l.pop_front(); }
#define opposing_controls(name, key1, key2) signed char name = (IsKeyDown(key1)) - (IsKeyDown(key2))
#define construct_object() root_objects = _root; SetPosition(_x, _y)
#define set_to_root() _root->push_back((SceneObject*)this)

//Libraries
#include <stdio.h>
#include <iostream>
#include <string>
#include <list>
#include <math.h>

//BaseClasses
#include "Game.h";
#include "Matrix2.h"
#include "Matrix2H.h"
#include "SceneObject.h"
#include "SpriteObject.h"
#include "Vector2D.h"
#include "Vector3D.h"