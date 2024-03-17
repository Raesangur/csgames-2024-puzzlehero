/**
 * ===============================================================================================
 * @file    smart-solver.cpp
 * @author  Pascal-Emmanuel Lachance
 * @p       <a href="https://www.github.com/Raesangur">Raesangur</a>
 *
 * ------------------------------------------------------------------------------------------------
 * @copyright Copyright (c) 2023 Pascal-Emmanuel Lachance | Raesangur
 *
 * @par License: <a href="https://opensource.org/license/mit/"> MIT </a>
 *               This project is released under the MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON INFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * ===============================================================================================
 */

/** ===============================================================================================
 *  INCLUDES
 */
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>


/** ===============================================================================================
 *  CLASS DEFINITIONS
 */
class RGB
{
public:
    RGB() = default;
    RGB(std::uint8_t r, std::uint8_t g, std::uint8_t b) : r{r}, g{g}, b{b}
    {
    }

    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;

    bool operator==(const RGB& rh) const
    {
        return r == rh.r && g == rh.g && b == rh.b;
    }
    bool operator!=(const RGB& rh) const
    {
        return !(*this == rh);
    }
};

class Piece
{
public:
    Piece() = default;
    Piece(RGB n, RGB s, RGB e, RGB w) : n{n}, s{s}, e{e}, w{w}
    {
    }

    RGB n;
    RGB s;
    RGB e;
    RGB w;

    Piece* nc = nullptr;
    Piece* sc = nullptr;
    Piece* ec = nullptr;
    Piece* wc = nullptr;

    bool operator==(const Piece& p) const
    {
        return n == p.n && s == p.s && e == p.e && w == p.w;
    }
};


/** ===============================================================================================
 *  FUNCTION DECLARATIONS
 */

template<typename CharIt>
void serialize(CharIt&& it, const std::vector<Piece>& pieces);

template<typename CharIt>
std::vector<Piece> deserialize(CharIt&& it, CharIt&& end);


template<typename CharIt>
void putByte(std::uint8_t byte, CharIt&& it);

template<typename CharIt>
std::uint8_t getByte(CharIt&& it, CharIt&& end);


/** ===============================================================================================
 *  FUNCTION DEFINITIONS
 */
template<typename CharIt>
void serialize(CharIt&& it, const std::vector<Piece>& pieces)
{
    std::size_t   length = pieces.size();
    std::uint8_t* l      = reinterpret_cast<std::uint8_t*>(&length);
    for(std::size_t i = 0U; i < sizeof(length); i++)
    {
        putByte(l[i], it);
    }

    for(const Piece& p : pieces)
    {
        putByte(p.n.r, it);
        putByte(p.n.g, it);
        putByte(p.n.b, it);

        putByte(p.s.r, it);
        putByte(p.s.g, it);
        putByte(p.s.b, it);

        putByte(p.e.r, it);
        putByte(p.e.g, it);
        putByte(p.e.b, it);

        putByte(p.w.r, it);
        putByte(p.w.g, it);
        putByte(p.w.b, it);

        if(pieces.empty())
        {
            for(std::size_t i = 0U; i < sizeof(void*) * 4U; i++)
            {
                putByte(0x00U, it);
            }
        }
        else
        {
            std::size_t indices[4] = {
              static_cast<std::size_t>(reinterpret_cast<long int>(p.nc - pieces.begin().base())),
              static_cast<std::size_t>(reinterpret_cast<long int>(p.sc - pieces.begin().base())),
              static_cast<std::size_t>(reinterpret_cast<long int>(p.ec - pieces.begin().base())),
              static_cast<std::size_t>(reinterpret_cast<long int>(p.wc - pieces.begin().base()))};

            for(std::size_t i = 0U; i < sizeof(indices); i++)
            {
                putByte(reinterpret_cast<uint8_t*>(indices)[i], it);
            }
        }
    }
}

template<typename CharIt>
std::vector<Piece> deserialize(CharIt&& it, CharIt&& end)
{
    std::size_t length{};
    for(std::size_t i = 0U; i < sizeof(length); i++)
    {
        std::uint8_t data = getByte(it, end);

        reinterpret_cast<std::uint8_t*>(&length)[i] = data;
    }

    std::vector<Piece> pieces(length);

    for(std::size_t i = 0U; i < length; i++)
    {
        Piece& p = pieces[i];
        p.n.r    = getByte(it, end);
        p.n.g    = getByte(it, end);
        p.n.b    = getByte(it, end);

        p.s.r = getByte(it, end);
        p.s.g = getByte(it, end);
        p.s.b = getByte(it, end);

        p.e.r = getByte(it, end);
        p.e.g = getByte(it, end);
        p.e.b = getByte(it, end);

        p.w.r = getByte(it, end);
        p.w.g = getByte(it, end);
        p.w.b = getByte(it, end);


        std::size_t indices[4]{};

        for(std::size_t i = 0U; i < sizeof(indices); i++)
        {
            std::uint8_t data = getByte(it, end);

            reinterpret_cast<std::uint8_t*>(&indices)[i] = data;
        }

        if (indices[0] == indices[1] && indices[2] == indices[3] && indices[0] == indices[2] && indices[0] == 0U)
        {
            /* Nothing here */
        }
        else
        {
            p.nc = &pieces[indices[0]];
            p.sc = &pieces[indices[1]];
            p.ec = &pieces[indices[2]];
            p.wc = &pieces[indices[3]];
        }
    }

    return pieces;
}


// https://stackoverflow.com/questions/523872/how-do-you-serialize-an-object-in-c
template<typename CharIt>
void putByte(std::uint8_t byte, CharIt&& it)
{
    *it = static_cast<char>(byte);
    ++it;
}

template<typename CharIt>
std::uint8_t getByte(CharIt&& it, CharIt&& end)
{
    if(it == end)
    {
        return 0x00U;
    }

    std::uint8_t byte = static_cast<std::uint8_t>(*it);
    it++;
    return byte;
}


/**
 * ------------------------------------------------------------------------------------------------
 */
int main(int argc, char** argv)
{
        std::ofstream ofile{"patches.bin"};
        serialize(std::ostreambuf_iterator<char>(ofile), vec);
        ofile.close();

        std::ifstream ifile{"patches.bin"};
        if(ifile)
        {
            std::vector<Piece> vec2 =
              deserialize(std::istreambuf_iterator<char>(ifile), std::istreambuf_iterator<char>());
        }
        ifile.close();
}



/**
 * ------------------------------------------------------------------------------------------------
 */
