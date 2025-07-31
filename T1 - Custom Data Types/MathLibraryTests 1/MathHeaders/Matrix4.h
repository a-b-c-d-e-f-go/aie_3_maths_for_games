#pragma once
namespace MathClasses
{
    struct Matrix4
    {
        //Essentials
        Matrix4(float _1 = 0, float _2 = 0, float _3 = 0, float _4 = 0, float _5 = 0, float _6 = 0, float _7 = 0, float _8 = 0, float _9 = 0, float _10 = 0, float _11 = 0, float _12 = 0, float _13 = 0, float _14 = 0, float _15 = 0, float _16 = 0) //Constructor (accepts any amount of floats, including zero).
        {
            m1 = _1; m5 = _5; m9 = _9; m13 = _13;
            m2 = _2; m6 = _6; m10 = _10; m14 = _14;
            m3 = _3; m7 = _7; m11 = _11; m15 = _15;
            m4 = _4; m8 = _8; m12 = _12; m16 = _16;
        }
        Matrix4(float arr[16]) //Overloaded Constructor (Array)
        {
            for (int i = 0; i < 16; i++) //Loop from 0-16.
            {
                v[i] = arr[i]; //Set value at i to input array.
            }
        }
        Matrix4(Vector4 _v1, Vector4 _v2, Vector4 _v3, Vector4 _v4) //Overloaded Constructor (Vector4)
        {
            axis[0] = _v1;
            axis[1] = _v2;
            axis[2] = _v3;
            axis[3] = _v4;
        }
        ~Matrix4() //Destructor
        {

        }
        union //16 floats (64 bytes)
        {
            struct //Numeric Form (Column-Major Order)
            {
                float m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16;
            };
            struct //Notation Form
            {
                float Xx, Xy, Xz, Xw, Yx, Yy, Yz, Yw, Zx, Zy, Zz, Zw, Tx, Ty, Tz, Tw;
            };

            //1D Float Array
            float v[16];

            //2D Float Array
            float mm[4][4];

            //1D Vector4 Array
            Vector4 axis[4];
        };

        //Compound Assignment Operators
        void operator *=(Matrix4 other) //Concatenate
        {
            (*this) = (*this) * other;
        }
        //Arithmetic Operators
        Matrix4 operator *(Matrix4 other) const
        {
            //Starts with all 0, added to throughout the loops, returned at the end.
            Matrix4 result;

            //Iterate through first matrix.
            for (size_t i = 0; i < 4; ++i)
            {
                //Current row from first matrix.
                Vector4 row(mm[0][i], mm[1][i], mm[2][i], mm[3][i]);

                //Iterate through second matrix.
                for (size_t j = 0; j < 4; ++j)
                {
                    //Get the dot product of j,i and the other matrix's column j.
                    //Result is assigned to row-by-row.
                    result.mm[j][i] = row.Dot(other.axis[j]);
                }
            }

            return result;
        }
        Vector4 operator *(Vector4 vec) const
        {
            return Vector4( //Treat the Vector4 as a 4x1 Matrix.
                Vector4(m1, m5, m9, m13).Dot(vec),
                Vector4(m2, m6, m10, m14).Dot(vec),
                Vector4(m3, m7, m11, m15).Dot(vec),
                Vector4(m4, m8, m12, m16).Dot(vec)
            );
        }
        //Misc Operators
        bool operator == (const Matrix4& other) const
        {
            //To account for floating imprecision.
            const float THRESHOLD = 0.00001f;
            bool equal = true; //Starts true.
            for (int i = 0; i < 16; i++) //Loop through both matrixes, looking at the same element in each.
            {
                if ((fabsf(other.v[i]) - fabsf(v[i])) > THRESHOLD) //If any value in the other is too far from this matrix's values, they aren't equal.
                {
                    equal = false;
                }
            }

            return equal;
        }
        bool operator != (const Matrix4& other) const
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
            for (int i = 1; i < 16; i++)
            {
                //Add a comma and the next value.
                s.append(", ");
                s.append(std::to_string(v[i]));
            }
            return s;
        }
        Matrix4 Transposed() const //Swaps rows & columns.
        {
            return Matrix4(m1, m5, m9, m13, m2, m6, m10, m14, m3, m7, m11, m15, m4, m8, m12, m16);
        }
        static Matrix4 MakeIdentity()
        {
            return Matrix4(
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            );
        }
        static Matrix4 MakeTranslation(float _x = 0, float _y = 0, float _z = 0)
        {
            return Matrix4( //Identity matrix with altered w column.
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                _x, _y, _z, 1
            );
        }
        static Matrix4 MakeRotateX(float _r)
        {
            return Matrix4( //Column major (which is why the -sinf is in the opposite place).
                1, 0, 0, 0,
                0, cosf(_r), sinf(_r), 0,
                0, -sinf(_r), cosf(_r), 0,
                0, 0, 0, 1
            );
        }
        static Matrix4 MakeRotateY(float _r)
        {
            return Matrix4( //Column major (which is why the -sinf is in the opposite place).
                cosf(_r), 0, sinf(_r), 0,
                0, 1, 0, 0,
                -sinf(_r), 0, cosf(_r), 0,
                0, 0, 0, 1
            );
        }
        static Matrix4 MakeRotateZ(float _r)
        {
            return Matrix4( //Column major (which is why the -sinf is in the opposite place).
                cosf(_r), -sinf(_r), 0, 0,
                sinf(_r), cosf(_r), 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            );
        }
        static Matrix4 MakeEuler(float _x = 0, float _y = 0, float _z = 0)
        {
            //Get 3 rotation matricies, 1 for each axis.
            Matrix4 x = MakeRotateX(_x);
            Matrix4 y = MakeRotateY(_y);
            Matrix4 z = MakeRotateZ(_z);

            //Combine rotations in Z, Y, X order.
            return (z * y * x);
        }
        static Matrix4 MakeScale(float _x = 1, float _y = 1, float _z = 1)
        {
            return Matrix4( //Identity matrix but S C A L E D.
                _x, 0, 0, 0,
                0, _y, 0, 0,
                0, 0, _z, 0,
                0, 0, 0, 1
            );
        }
        //Vector3 Versions
        static Matrix4 MakeTranslation(Vector3 vec)
        {
            return MakeTranslation(vec.x, vec.y, vec.z);
        }
        static Matrix4 MakeEuler(Vector3 vec)
        {
            return MakeEuler(vec.x, vec.y, vec.z);
        }
        static Matrix4 MakeScale(Vector3 vec)
        {
            return MakeScale(vec.x, vec.y, vec.z);
        }
    };
    static Vector4 operator *(Vector4& vec, Matrix4& mat) //Reversed Multiply Operator (Vector3)
    {
        return mat * vec;
    }
}