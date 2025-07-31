#pragma once

#include "Matrix2.h"
#include "Matrix2H.h"
#include "Vector2D.h"
#include "Vector3D.h"

using namespace MathClasses;

namespace MathClasses
{
    struct Matrix2H //Homogenous 2D Matrix
    {
        //Essentials
        Matrix2H() //Constructor
        {
            m1 = 0; m4 = 0; m7 = 0;
            m2 = 0; m5 = 0; m8 = 0;
            m3 = 0; m6 = 0; m9 = 0;
        }
        Matrix2H(float _1, float _2, float _3, float _4, float _5, float _6, float _7, float _8, float _9) //Overloaded Constructor (float)
        {
            m1 = _1; m4 = _4; m7 = _7;
            m2 = _2; m5 = _5; m8 = _8;
            m3 = _3; m6 = _6; m9 = _9;
        }
        Matrix2H(float arr[9]) //Overloaded Constructor (Array)
        {
            for (int i = 0; i < 9; i++) //Loop from 0-9.
            {
                v[i] = arr[i]; //Set value at i to input array.
            }
        }
        Matrix2H(Vector3D _v1, Vector3D _v2, Vector3D _v3) //Overloaded Constructor (Vector3D)
        {
            axis[0] = _v1;
            axis[1] = _v2;
            axis[2] = _v3;
        }
        ~Matrix2H() //Destructor
        {

        }
        union //9 floats (36 bytes)
        {
            struct //Numeric Form (Column-Major Order)
            {
                float m1, m2, m3, m4, m5, m6, m7, m8, m9;
            };
            struct //Notation Form
            {
                float Xx, Xy, Xw, Yx, Yy, Yw, Tx, Ty, Tw;
            };

            //1D Float Array
            float v[9];

            //2D Float Array
            float mm[3][3];

            //1D Vector3D Array
            Vector3D axis[3];
        };

        //Compound Assignment Operators
        void operator *=(Matrix2H other) //Concatenate
        {
            (*this) = (*this) * other;
        }
        //Arithmetic Operators
        Matrix2H operator *(Matrix2H other) const
        {
            //Starts with all 0, added to throughout the loops, returned at the end.
            Matrix2H result;

            //Iterate through first matrix.
            for (size_t i = 0; i < 3; ++i)
            {
                //Current row from first matrix.
                Vector3D row(mm[0][i], mm[1][i], mm[2][i]);

                //Iterate through second matrix.
                for (size_t j = 0; j < 3; ++j)
                {
                    //Get the dot product of j,i and the other matrix's column j.
                    //Result is assigned to row-by-row.
                    result.mm[j][i] = row.Dot(other.axis[j]);
                }
            }

            return result;
        }
        Vector3D operator *(Vector3D vec) const
        {
            return Vector3D( //Treat the Vector3D as a 3x1 Matrix.
                Vector3D(m1, m4, m7).Dot(vec),
                Vector3D(m2, m5, m8).Dot(vec),
                Vector3D(m3, m6, m9).Dot(vec)
            );
        }
        //Misc Operators
        bool operator == (const Matrix2H& other) const
        {
            //To account for floating imprecision.
            const float THRESHOLD = 0.00001f;
            bool equal = true; //Starts true.
            for (int i = 0; i < 9; i++) //Loop through both matrixes, looking at the same element in each.
            {
                if ((fabsf(other.v[i]) - fabsf(v[i])) > THRESHOLD) //If any value in the other is too far from this matrix's values, they aren't equal.
                {
                    equal = false;
                }
            }

            return equal;
        }
        bool operator != (const Matrix2H& other) const
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
            for (int i = 1; i < 9; i++)
            {
                //Add a comma and the next value.
                s.append(", ");
                s.append(std::to_string(v[i]));
            }
            return s;
        }
        Matrix2H Transposed() const //Swaps rows & columns.
        {
            return Matrix2H(m1, m4, m7, m2, m5, m8, m3, m6, m9);
        }
        static Matrix2H MakeIdentity()
        {
            return Matrix2H(
                1, 0, 0,
                0, 1, 0,
                0, 0, 1
            );
        }
        static Matrix2H MakeTranslation(float _x = 0, float _y = 0)
        {
            return Matrix2H( //2D vector being translated using T dimension.
                1, 0, 0,
                0, 1, 0,
                _x, _y, 1
            );
        }
        static Matrix2H MakeRotation(float _r)
        {
            return Matrix2H( //Column major (which is why the -sinf is in the opposite place).
                cosf(_r), sinf(_r), 0,
                -sinf(_r), cosf(_r), 0,
                0, 0, 1
            );
        }
        static Matrix2H MakeScale(float _x = 1, float _y = 1)
        {
            return Matrix2H( //Identity matrix but S C A L E D.
                _x, 0, 0,
                0, _y, 0,
                0, 0, 0
            );
        }
        //Vector3D Versions
        static Matrix2H MakeTranslation(Vector2 vec)
        {
            return MakeTranslation(vec.x, vec.y);
        }
        static Matrix2H MakeScale(Vector2 vec)
        {
            return MakeScale(vec.x, vec.y);
        }
    };
}