#pragma once
namespace MathClasses
{
    struct Matrix3
    {
        //Essentials
        Matrix3() //Constructor
        {
            m1 = 0; m4 = 0; m7 = 0;
            m2 = 0; m5 = 0; m8 = 0;
            m3 = 0; m6 = 0; m9 = 0;
        }
        Matrix3(float _1, float _2, float _3, float _4, float _5, float _6, float _7, float _8, float _9) //Overloaded Constructor (float)
        {
            m1 = _1; m4 = _4; m7 = _7;
            m2 = _2; m5 = _5; m8 = _8;
            m3 = _3; m6 = _6; m9 = _9;
        }
        Matrix3(float arr[9]) //Overloaded Constructor (Array)
        {
            for (int i = 0; i < 9; i++) //Loop from 0-9.
            {
                v[i] = arr[i]; //Set value at i to input array.
            }
        }
        Matrix3(Vector3 _v1, Vector3 _v2, Vector3 _v3) //Overloaded Constructor (Vector3)
        {
            axis[0] = _v1;
            axis[1] = _v2;
            axis[2] = _v3;
        }
        ~Matrix3() //Destructor
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
                float Xx, Xy, Xz, Yx, Yy, Yz, Zx, Zy, Zz;
            };

            //1D Float Array
            float v[9];

            //2D Float Array
            float mm[3][3];

            //1D Vector3 Array
            Vector3 axis[3];
        };

        //Compound Assignment Operators
        void operator *=(Matrix3 other) //Concatenate
        {
            (*this) = (*this) * other;
        }
        //Arithmetic Operators
        Matrix3 operator *(Matrix3 other) const
        {
            //Starts with all 0, added to throughout the loops, returned at the end.
            Matrix3 result;

            //Iterate through first matrix.
            for (size_t i = 0; i < 3; ++i)
            {
                //Current row from first matrix.
                Vector3 row(mm[0][i], mm[1][i], mm[2][i]);

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
        Vector3 operator *(Vector3 vec) const
        {
            return Vector3( //Treat the Vector3 as a 3x1 Matrix.
                Vector3(m1, m4, m7).Dot(vec),
                Vector3(m2, m5, m8).Dot(vec),
                Vector3(m3, m6, m9).Dot(vec)
            );
        }
        //Misc Operators
        bool operator == (const Matrix3& other) const
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
        bool operator != (const Matrix3& other) const
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
        operator float*() { return v; } //Cast to Float Array
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
        Matrix3 Transposed() const //Swaps rows & columns.
        {
            return Matrix3(m1, m4, m7, m2, m5, m8, m3, m6, m9);
        }
        static Matrix3 MakeIdentity()
        {
            return Matrix3(
                1, 0, 0,
                0, 1, 0,
                0, 0, 1
            );
        }
        static Matrix3 MakeTranslation(float _x = 0, float _y = 0, float _z = 0)
        {
            return MakeIdentity(); //A translation matrix without the T column is just the identity matrix.
        }
        static Matrix3 MakeRotateX(float _r)
        {
            return Matrix3( //Column major (which is why the -sinf is in the opposite place).
                1, 0, 0,
                0, cosf(_r), sinf(_r),
                0, -sinf(_r), cosf(_r)
            );
        }
        static Matrix3 MakeRotateY(float _r)
        {
            return Matrix3( //Column major (which is why the -sinf is in the opposite place).
                cosf(_r), 0, sinf(_r),
                0, 1, 0,
                -sinf(_r), 0, cosf(_r)
            );
        }
        static Matrix3 MakeRotateZ(float _r)
        {
            return Matrix3( //Column major (which is why the -sinf is in the opposite place).
                cosf(_r), -sinf(_r), 0,
                sinf(_r), cosf(_r), 0,
                0, 0, 1
            );
        }
        static Matrix3 MakeEuler(float _x = 0, float _y = 0, float _z = 0)
        {
            //Get 3 rotation matricies, 1 for each axis.
            Matrix3 x = MakeRotateX(_x);
            Matrix3 y = MakeRotateY(_y);
            Matrix3 z = MakeRotateZ(_z);

            //Combine rotations in Z, Y, X order.
            return (z * y * x);
        }
        static Matrix3 MakeScale(float _x = 1, float _y = 1, float _z = 1)
        {
            return Matrix3( //Identity matrix but S C A L E D.
                _x, 0, 0,
                0, _y, 0,
                0, 0, _z
            );
        }
        //Vector3 Versions
        static Matrix3 MakeTranslation(Vector3 vec)
        {
            return MakeTranslation(vec.x, vec.y, vec.z);
        }
        static Matrix3 MakeEuler(Vector3 vec)
        {
            return MakeEuler(vec.x, vec.y, vec.z);
        }
        static Matrix3 MakeScale(Vector3 vec)
        {
            return MakeScale(vec.x, vec.y, vec.z);
        }
	};
    static Vector3 operator *(Vector3& vec, Matrix3& mat) //Reversed Multiply Operator (Vector3)
    {
        return mat * vec;
    }
}