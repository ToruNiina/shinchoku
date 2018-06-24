#ifndef SHINCHOKU_FORMAT_HPP
#define SHINCHOKU_FORMAT_HPP
#include "elements.hpp"
#include <ostream>
#include <array>
#include <cmath>
#include <cstdint>

namespace shnchk
{

template<std::size_t N>
struct format_impl
{
    format_impl() noexcept {buffer.front() = '\r';}

    const char* invoke(double ratio) noexcept
    {
        char* front = buffer.data() + 1;

        const std::uint32_t percent = std::min<std::uint32_t>(
                static_cast<std::uint32_t>(ratio * 100), 100u);
        front += std::sprintf(front, "%3d", percent);
        *(front++) = '%';
        *(front++) = '|';
        if(percent == 100)
        {
            for(std::size_t i=0; i<N; ++i)
            {
                *(front++) = elements::full[0];
                *(front++) = elements::full[1];
                *(front++) = elements::full[2];
            }
            *(front++) = '|';
            *front = '\0';
            return buffer.data();
        }

        const double      ratioN   = ratio * N;
        const std::size_t num_full = std::floor(ratioN);
        for(std::size_t i=0; i<num_full; ++i)
        {
            *(front++) = elements::full[0];
            *(front++) = elements::full[1];
            *(front++) = elements::full[2];
        }

        switch(static_cast<std::uint32_t>(ratioN * 8u) % 8u)
        {
            case 7: {*(front++) = elements::w7_8[0]; *(front++) = elements::w7_8[1]; *(front++) = elements::w7_8[2]; break;}
            case 6: {*(front++) = elements::w6_8[0]; *(front++) = elements::w6_8[1]; *(front++) = elements::w6_8[2]; break;}
            case 5: {*(front++) = elements::w5_8[0]; *(front++) = elements::w5_8[1]; *(front++) = elements::w5_8[2]; break;}
            case 4: {*(front++) = elements::w4_8[0]; *(front++) = elements::w4_8[1]; *(front++) = elements::w4_8[2]; break;}
            case 3: {*(front++) = elements::w3_8[0]; *(front++) = elements::w3_8[1]; *(front++) = elements::w3_8[2]; break;}
            case 2: {*(front++) = elements::w2_8[0]; *(front++) = elements::w2_8[1]; *(front++) = elements::w2_8[2]; break;}
            case 1: {*(front++) = elements::w1_8[0]; *(front++) = elements::w1_8[1]; *(front++) = elements::w1_8[2]; break;}
            case 0: {*(front++) = ' '; break;}
        }
        for(std::size_t i=0, e=N-num_full-1; i<e; ++i)
        {
            *(front++) = ' ';
        }
        *(front++) = '|';
        *front = '\0';
        return buffer.data();
    }

    std::array<char, N*3+9> buffer;
};

template<std::size_t N = 40>
void format(std::ostream& os, const double ratio)
{
    format_impl<N> fmt;
    os << fmt.invoke(ratio) << std::flush;
    return;
}

} // shnchk
#endif // SHINCHOKU_FORMAT_HPP
