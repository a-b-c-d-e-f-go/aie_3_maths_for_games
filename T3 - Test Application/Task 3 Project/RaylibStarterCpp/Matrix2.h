#pragma once

#include "Matrix2.h"
#include "Matrix2H.h"
#include "Vector2D.h"
#include "Vector3D.h"

using namespace MathClasses;

namespace MathClasses
{
    struct Matrix2
    {
        //Essentials
        Matrix2() //Constructor
        {
            m1 = 0; m3 = 0;
            m2 = 0; m4 = 0;
        }
        Matrix2(float _1, float _2, float _3, float _4) //Overloaded Constructor (float)
        {
            m1 = _1; m3 = _3;
            m2 = _2; m4 = _4;
        }
        Matrix2(float arr[4]) //Overloaded Constructor (Array)
        {
            for (int i = 0; i < 4; i++) //Loop from 0-9.
            {
                v[i] = arr[i]; //Set value at i to input array.
            }
        }
        Matrix2(Vector2D _v1, Vector2D _v2) //Overloaded Constructor (Vector3D)
        {
            axis[0] = _v1;
            axis[1] = _v2;
        }
        ~Matrix2() //Destructor
        {

        }
        union //4 floats (16 bytes)
        {
            struct //Numeric Form (Column-Major Order)
            {
                float m1, m2, m3, m4;
            };
            struct //Notation Form
            {
                float Xx, Xy, Yx, Yy;
            };

            //1D Float Array
            float v[4];

            //2D Float Array
            float mm[2][2];

            //1D Vector2D Array
            Vector2D axis[2];
        };
        //Compound Assignment Operators
        void operator *=(Matrix2 other) //Concatenate
        {
            (*this) = (*this) * other;
        }
        //Arithmetic Operators
        Matrix2 operator *(Matrix2 other) const
        {
            //Starts with all 0, added to throughout the loops, returned at the end.
            Matrix2 result;

            //Iterate through first matrix.
            for (size_t i = 0; i < 2; ++i)
            {
                //Current row from first matrix.
                Vector2D row(mm[0][i], mm[1][i]);

                //Iterate through second matrix.
                for (size_t j = 0; j < 2; ++j)
                {
                    //Get the dot product of j,i and the other matrix's column j.
                    //Result is assigned to row-by-row.
                    result.mm[j][i] = row.Dot(other.axis[j]);
                }
            }

            return result;
        }
        Vector2D operator *(Vector2D vec) const
        {
            return Vector2D( //Treat the Vector3D as a 3x1 Matrix.
                Vector2D(m1, m3).Dot(vec),
                Vector2D(m2, m4).Dot(vec)
            );
        }
        //Misc Operators
        bool operator == (const Matrix2& other) const
        {
            //To account for floating imprecision.
            const float THRESHOLD = 0.00001f;
            bool equal = true; //Starts true.
            for (int i = 0; i < 4; i++) //Loop through both matrixes, looking at the same element in each.
            {
                if ((fabsf(other.v[i]) - fabsf(v[i])) > THRESHOLD) //If any value in the other is too far from this matrix's values, they aren't equal.
                {
                    equal = false;
                }
            }

            return equal;
        }
        bool operator != (const Matrix2& other) const
        {
            return !(*this == other);
        }
        float& operator [](int index) //Subscript Operator
        {
            return v[index];
        }
        const float& operator [](int index) const //Subscript Operator - Const Overload
        {
            return v[index];
        }
        operator float* () { return v; } //Cast to Float Array
        operator const float* () const { return v; } //Cast to Float Array - Const Overload
        //Functions
        std::string ToString() const
        {
            std::string s = std::to_string(v[0]); //Start with the first value and no comma. It's much of a muchness whether you want to use ", value" and make the first one an exception or use "value, " and make the last one an exception.
            for (int i = 1; i < 4; i++)
            {
                //Add a comma and the next value.
                s.append(", ");
                s.append(std::to_string(v[i]));
            }
            return s;
        }
        Matrix2 Transposed() const //Swaps rows & columns.
        {
            return Matrix2(m1, m3, m2, m4);
        }
        static Matrix2 MakeIdentity()
        {
            return Matrix2(
                1, 0,
                0, 1
            );
        }
        static Matrix2 MakeTranslation(float _x = 0, float _y = 0)
        {
            return MakeIdentity(); //A translation matrix without the T column is just the identity matrix.
        }
        static Matrix2 MakeRotation(float _r)
        {
            return Matrix2( //Column major (which is why the -sinf is in the opposite place).
                cosf(_r), sinf(_r),
                -sinf(_r), cosf(_r)
            );
        }
        static Matrix2 MakeScale(float _x = 1, float _y = 1)
        {
            return Matrix2( //Identity matrix but S C A L E D.
                _x, 0,
                0, _y
            );
        }
        //Vector2D Versions
        static Matrix2 MakeTranslation(Vector2D vec)
        {
            return MakeTranslation(vec.x, vec.y);
        }
        static Matrix2 MakeScale(Vector2D vec)
        {
            return MakeScale(vec.x, vec.y);
        }
    };
}