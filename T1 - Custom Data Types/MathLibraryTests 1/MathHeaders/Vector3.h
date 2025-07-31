#pragma once

namespace MathClasses
{
    struct Vector3
    {
        //Essentials
        Vector3() //Constructor - Values default to zero.
        {
            x = 0;
            y = 0;
            z = 0;
        }
        Vector3(float _x, float _y, float _z) //Overloaded Constructor
        {
            x = _x;
            y = _y;
            z = _z;
        }
        ~Vector3() //Destructor
        {

        }
        union //3 floats (12 bytes)
        {
            struct { float x, y, z; };  //Anonymous Struct (xyz)
            struct { float r, g, b; };  //Anonymous Struct (rgb)
            float data[3];              //Array
        };

        //Compound Assignment Operators
        Vector3& operator +=(Vector3 other) //Add (Assignment) Operator
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return (*this);
        }
        Vector3& operator -=(Vector3 other) //Subtract (Assignment) Operator
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return (*this);
        }
        Vector3& operator *=(Vector3 other) //Multiply (Assignment) Operator
        {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            return (*this);
        }
        Vector3& operator /=(Vector3 other) //Divide (Assignment) Operator
        {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            return (*this);
        }
        Vector3& operator *=(float sca) //Multiply (Assignment) Operator - Float Input
        {
            x *= sca;
            y *= sca;
            z *= sca;
            return (*this);
        }
        Vector3& operator /=(float sca) //Divide (Assignment) Operator - Float Input
        {
            x /= sca;
            y /= sca;
            z /= sca;
            return (*this);
        }
        //Arithmetic Operators
        Vector3 operator +(Vector3 other) //Add Operator - Creates a copy and adds the second vector to it.
        {
            Vector3 copy = (*this);
            copy += other;
            return copy;
        }
        Vector3 operator -(Vector3 other) //Subtract Operator - Same process as above.
        {
            Vector3 copy = (*this);
            copy -= other;
            return copy;
        }
        Vector3 operator *(Vector3 other) //Multiply Operator - Same process as above.
        {
            Vector3 copy = (*this);
            copy *= other;
            return copy;
        }
        Vector3 operator /(Vector3 other) //Divide Operator - Same process as above.
        {
            Vector3 copy = (*this);
            copy /= other;
            return copy;
        }
        Vector3 operator *(float sca) //Multiply Operator - Float Input
        {
            Vector3 copy = (*this);
            copy *= sca;
            return copy;
        }
        Vector3 operator /(float sca) //Divide Operator - Float Input
        {
            Vector3 copy = (*this);
            copy /= sca;
            return copy;
        }
        //Misc Operators
        bool operator == (const Vector3& other) const
        {
            //Get distances between coordinates.
            float xd = fabsf(x - other.x);
            float yd = fabsf(y - other.y);
            float zd = fabsf(z - other.z);

            //To account for floating imprecision.
            const float THRESHOLD = 0.00003f;

            //If the combined distance is small enough, it's probably the same.
            return (xd + yd + zd) < THRESHOLD;
        }
        bool operator != (const Vector3& other) const
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
            return sqrtf(x * x + y * y + z * z);
        }
        float MagnitudeSqr() const //More efficient if you just want to know if one object is closer to something than the other instead of needing their actual distances.
        {
            return x * x + y * y + z * z;
        }
        float Distance(const Vector3& other) //Distance between 2 vectors using Magnitude.
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
            }
            return;
        }
        Vector3 Normalised() const //Returns a normalised copy of the vector.
        {
            Vector3 copy = (*this);
            copy.Normalise();

            return copy;
        }
        const float Dot(const Vector3& other) const //AxBx + AyBy + AzBz
        {
            return (x * other.x) + (y * other.y) + (z * other.z);
        }
        Vector3 Cross(const Vector3& other) //Right-hand implementation.
        {
            return Vector3(y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x);
        }

        //For debugging.
        std::string ToString() const
        {
            return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z); //Eg. 1, 2, 3
        }
	};
    static Vector3 operator *(const float& sca, Vector3& vec) //Reversed Multiply Operator
    {
        return vec * sca;
    }
}