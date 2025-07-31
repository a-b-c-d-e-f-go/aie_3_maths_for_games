#pragma once

using uc = unsigned char;

namespace MathClasses
{
    struct Colour
    {
        std::uint32_t colour = 255; //Where the colour value is stored. Contains 4 bytes and is unsigned to make bitshifts work properly.
        Colour(uc red = 0, uc green = 0, uc blue = 0, uc alpha = 255) //Imagine having a non-overloaded constructor.
        {
            SetRed(red);
            SetGreen(green);
            SetBlue(blue);
            SetAlpha(alpha);
        }

        const uc GetByte(uc index) const //Makes writing all the other get functions easier. If this weren't a struct it'd probably be private.
        {
            return (colour >> (index * 8)); //Offsets by the amount of bytes (8 bits each) and trims everything after when converting to unsigned char.
        }
        void SetByte(uc index, uc input) //Makes writing all the other set functions easier. If this weren't a struct it'd probably be private.
        {
            //Slide the input bits into the correct position.
            unsigned int v = (unsigned int)input << (index * 8);

            //Create a byte of eight 1s and move it to where the byte we're targeting is.
            //This will be our mask to replace the old byte.
            unsigned int m = (unsigned int)0xff << (index * 8);

            //Invert the mask, using the and operator so that anything where the mask's 0s are is set to 0.
            colour = colour & ~m;

            //Put the new colour values into place.
            colour = colour | v;
        }

        const uc GetRed() const
        {
            return GetByte(3); //RGBA are 3210 respectively.
        }
        void SetRed(uc red)
        {
            SetByte(3, red); //RGBA are 3210 respectively.
        }

        const uc GetGreen() const
        {
            return GetByte(2); //RGBA are 3210 respectively.
        }
        void SetGreen(uc green)
        {
            SetByte(2, green); //RGBA are 3210 respectively.
        }

        const uc GetBlue() const
        {
            return GetByte(1); //RGBA are 3210 respectively.
        }
        void SetBlue(uc blue)
        {
            SetByte(1, blue); //RGBA are 3210 respectively.
        }

        const uc GetAlpha() const
        {
            return GetByte(0); //RGBA are 3210 respectively.
        }
        void SetAlpha(uc alpha)
        {
            SetByte(0, alpha); //RGBA are 3210 respectively.
        }

        bool operator == (const Colour& other) const
        {
            return (colour == other.colour); //If there's one thing all this bitwise wizardry makes easier, it's checking equality. One variable, one check.
        }
        bool operator != (const Colour& other) const
        {
            return !(*this == other);
        }
    };
}