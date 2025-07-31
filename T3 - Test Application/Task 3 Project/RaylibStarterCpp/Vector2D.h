#pragma once
#include <math.h>
#include <string>

namespace MathClasses
{
    struct Vector2D
    {
        //Essentials
        Vector2D() //Constructor - Values default to zero.
        {
            x = 0;
            y = 0;
        }
        Vector2D(float _x, float _y) //Overloaded Constructor
        {
            x = _x;
            y = _y;
        }
        ~Vector2D() //Destructor
        {

        }
        union //2 floats (8 bytes)
        {
            struct { float x, y; };  //Anonymous Struct (xyz)
            float data[2];              //Array
        };

        //Compound Assignment Operators
        Vector2D& operator +=(Vector2D other) //Add (Assignment) Operator
        {
            x += other.x;
            y += other.y;
            return (*this);
        }
        Vector2D& operator -=(Vector2D other) //Subtract (Assignment) Operator
        {
            x -= other.x;
            y -= other.y;
            return (*this);
        }
        Vector2D& operator *=(Vector2D other) //Multiply (Assignment) Operator
        {
            x *= other.x;
            y *= other.y;
            return (*this);
        }
        Vector2D& operator /=(Vector2D other) //Divide (Assignment) Operator
        {
            x /= other.x;
            y /= other.y;
            return (*this);
        }
        Vector2D& operator *=(float sca) //Multiply (Assignment) Operator - Float Input
        {
            x *= sca;
            y *= sca;
            return (*this);
        }
        Vector2D& operator /=(float sca) //Divide (Assignment) Operator - Float Input
        {
            x /= sca;
            y /= sca;
            return (*this);
        }
        //Arithmetic Operators
        Vector2D operator +(Vector2D other) //Add Operator - Creates a copy and adds the second vector to it.
        {
            Vector2D copy = (*this);
            copy += other;
            return copy;
        }
        Vector2D operator -(Vector2D other) //Subtract Operator - Same process as above.
        {
            Vector2D copy = (*this);
            copy -= other;
            return copy;
        }
        Vector2D operator *(Vector2D other) //Multiply Operator - Same process as above.
        {
            Vector2D copy = (*this);
            copy *= other;
            return copy;
        }
        Vector2D operator /(Vector2D other) //Divide Operator - Same process as above.
        {
            Vector2D copy = (*this);
            copy /= other;
            return copy;
        }
        Vector2D operator *(float sca) //Multiply Operator - Float Input
        {
            Vector2D copy = (*this);
            copy *= sca;
            return copy;
        }
        Vector2D operator /(float sca) //Divide Operator - Float Input
        {
            Vector2D copy = (*this);
            copy /= sca;
            return copy;
        }
        //Misc Operators
        bool operator == (const Vector2D& other) const
        {
            //Get distances between coordinates.
            float xd = fabsf(x - other.x);
            float yd = fabsf(y - other.y);

            //To account for floating imprecision.
            const float THRESHOLD = 0.00002f;

            //If the combined distance is small enough, it's probably the same.
            return (xd + yd) < THRESHOLD;
        }
        bool operator != (const Vector2D& other) const
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
            return sqrtf(x * x + y * y);
        }
        float MagnitudeSqr() const //More efficient if you just want to know if one object is closer to something than the other instead of needing their actual distances.
        {
            return x * x + y * y;
        }
        float Distance(const Vector2D& other) //Distance between 2 vectors using Magnitude.
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
            }
            return;
        }
        Vector2D Normalised() const //Returns a normalised copy of the vector.
        {
            Vector2D copy = (*this);
            copy.Normalise();

            return copy;
        }
        const float Dot(const Vector2D& other) const //AxBx + AyBy + AzBz
        {
            return (x * other.x) + (y * other.y);
        }

        //For debugging.
        std::string ToString() const
        {
            return std::to_string(x) + ", " + std::to_string(y); //Eg. 1, 2
        }
    };
}