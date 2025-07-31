#pragma once

namespace MathClasses
{
    struct Vector4
    {
        //Essentials
        Vector4(float _x = 0, float _y = 0, float _z = 0, float _w = 0) //Constructor (accepts any amount of floats, including zero).
        {
            x = _x;
            y = _y;
            z = _z;
            w = _w;
        }
        ~Vector4() //Destructor
        {

        }
        union //4 floats (16 bytes)
        {
            struct { float x, y, z, w; };  //Anonymous Struct (xyzw)
            struct { float r, g, b, a; };  //Anonymous Struct (rgba)
            float data[4];              //Array
        };

        //Compound Assignment Operators
        Vector4& operator +=(Vector4 other) //Add (Assignment) Operator
        {
            x += other.x;
            y += other.y;
            z += other.z;
            w += other.w;
            return (*this);
        }
        Vector4& operator -=(Vector4 other) //Subtract (Assignment) Operator
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            w -= other.w;
            return (*this);
        }
        Vector4& operator *=(Vector4 other) //Multiply (Assignment) Operator
        {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            w *= other.w;
            return (*this);
        }
        Vector4& operator /=(Vector4 other) //Divide (Assignment) Operator
        {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            w /= other.w;
            return (*this);
        }
        Vector4& operator *=(float sca) //Multiply (Assignment) Operator - Float Input
        {
            x *= sca;
            y *= sca;
            z *= sca;
            w *= sca;
            return (*this);
        }
        Vector4& operator /=(float sca) //Divide (Assignment) Operator - Float Input
        {
            x /= sca;
            y /= sca;
            z /= sca;
            w /= sca;
            return (*this);
        }
        //Arithmetic Operators
        Vector4 operator +(Vector4 other) //Add Operator - Creates a copy and adds the second vector to it.
        {
            Vector4 copy = (*this);
            copy += other;
            return copy;
        }
        Vector4 operator -(Vector4 other) //Subtract Operator - Same process as above.
        {
            Vector4 copy = (*this);
            copy -= other;
            return copy;
        }
        Vector4 operator *(Vector4 other) //Multiply Operator - Same process as above.
        {
            Vector4 copy = (*this);
            copy *= other;
            return copy;
        }
        Vector4 operator /(Vector4 other) //Divide Operator - Same process as above.
        {
            Vector4 copy = (*this);
            copy /= other;
            return copy;
        }
        Vector4 operator *(float sca) //Multiply Operator - Float Input
        {
            Vector4 copy = (*this);
            copy *= sca;
            return copy;
        }
        Vector4 operator /(float sca) //Divide Operator - Float Input
        {
            Vector4 copy = (*this);
            copy /= sca;
            return copy;
        }
        //Misc Operators
        bool operator == (const Vector4& other) const
        {
            //Get distances between coordinates.
            float xd = fabsf(x - other.x);
            float yd = fabsf(y - other.y);
            float zd = fabsf(z - other.z);
            float wd = fabsf(w - other.w);

            //To account for floating imprecision.
            const float THRESHOLD = 0.00004f;

            //If the combined distance is small enough, it's probably the same.
            return (xd + yd + zd + wd) < THRESHOLD;
        }
        bool operator != (const Vector4& other) const
        {
            return !(*this == other);
        }
        float& operator [](int index) //Subscript Operator
        {
            return data[index];
        }
        const float& operator [](int index) const //Subscript Operator - Const Overload
        {
            return data[index];
        }
        operator float* () { return data; } //Cast to Float Array
        operator const float* () const { return data; } //Cast to Float Array - Const Overload

        //Functions
        float Magnitude() const //The square root of the individual coordinates squared is the distance.
        {
            return sqrtf(x * x + y * y + z * z + w * w);
        }
        float MagnitudeSqr() const //More efficient if you just want to know if one object is closer to something than the other instead of needing their actual distances.
        {
            return x * x + y * y + z * z + w * w;
        }
        float Distance(const Vector4& other) //Distance between 2 vectors using Magnitude.
        {
            return (*this - other).Magnitude();
        }
        void Normalise() //Normalises the vector.
        {
            float m = Magnitude(); //Get the magnitude.
            if (m != 0) //Can't divide by zero, and can't get a direction from a zero vector.
            {
                //Divide all coordinates by the magnitue so that the magnitude is 1.
                x /= m;
                y /= m;
                z /= m;
                w /= m;
            }
            return;
        }
        Vector4 Normalised() const //Returns a normalised copy of the vector.
        {
            Vector4 copy = (*this);
            copy.Normalise();

            return copy;
        }
        const float Dot(const Vector4& other) const //AxBx + AyBy + AzBz
        {
            return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
        }
        Vector4 Cross(const Vector4& other) //Nearly identical to the 3-D implementation. The 4th dimension, W, is left as zero.
        {
            return Vector4(y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x,
                0);
        }

        //For debugging.
        std::string ToString() const
        {
            return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w); //Eg. 1, 2, 3
        }
    };
    static Vector4 operator *(const float& sca, Vector4& vec) //Reversed Multiply Operator
    {
        return vec * sca;
    }
}