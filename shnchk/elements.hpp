#ifndef SHINCHOKU_ELEMENTS_HPP
#define SHINCHOKU_ELEMENTS_HPP

namespace shnchk
{

struct elements
{
    static constexpr const char* zero = u8" "; // whitespace
    static constexpr const char* full = u8"█"; // U+2588 Full block

    static constexpr const char* w7_8 = u8"▉"; // U+2589 Left seven eighths block
    static constexpr const char* w6_8 = u8"▊"; // U+258A Left three quarters block
    static constexpr const char* w5_8 = u8"▋"; // U+258B Left five eighths block
    static constexpr const char* w4_8 = u8"▌"; // U+258C Left half block
    static constexpr const char* w3_8 = u8"▍"; // U+258D Left three eighths block
    static constexpr const char* w2_8 = u8"▎"; // U+258E Left one quarter block
    static constexpr const char* w1_8 = u8"▏"; // U+258F Left one eighth block

    static constexpr const char* h1_8 = u8"▁"; // U+2581 Lower one eighth block
    static constexpr const char* h2_8 = u8"▂"; // U+2582 Lower one quarter block
    static constexpr const char* h3_8 = u8"▃"; // U+2583 Lower three eighths block
    static constexpr const char* h4_8 = u8"▄"; // U+2584 Lower half block
    static constexpr const char* h5_8 = u8"▅"; // U+2585 Lower five eighths block
    static constexpr const char* h6_8 = u8"▆"; // U+2586 Lower three quarters block
    static constexpr const char* h7_8 = u8"▇"; // U+2587 Lower seven eighths block
};

} // shnchk
#endif// SHINCHOKU_ELEMENTS_HPP_
