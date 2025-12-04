// fade.h – Exact recreation of the 17 gradients from the README.md
#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <cstdint>


namespace ansi {
    inline std::string fg(int r, int g, int b) {
        return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
    }

    constexpr const char reset[] = "\033[0m";  // Works great too
}
struct RGB { int r, g, b; };

inline RGB lerp(const RGB& a, const RGB& b, float t) {
    return {
        int(a.r + (b.r - a.r) * t),
        int(a.g + (b.g - a.g) * t),
        int(a.b + (b.b - a.b) * t)
    };
}

inline std::string apply_gradient(const std::string& text, const RGB& start, const RGB& end) {
    if (text.empty()) return text;

    std::ostringstream out;
    std::vector<std::string> lines;
    std::istringstream iss(text);
    for (std::string line; std::getline(iss, line);)
        lines.push_back(std::move(line));

    for (const auto& line : lines) {
        if (line.empty()) { out << '\n'; continue; }
        size_t n = line.size();
        for (size_t i = 0; i < n; ++i) {
            float t = n == 1 ? 0.0f : static_cast<float>(i) / (n - 1);
            RGB c = lerp(start, end, t);
            out << ansi::fg(c.r, c.g, c.b) << line[i];
        }
        out << ansi::reset << '\n';
    }
    return out.str();
}

inline std::string rainbow_gradient(const std::string& text) {
    std::vector<RGB> colors = {
        {255,   0,   0}, // red
        {255, 165,   0}, // orange
        {255, 255,   0}, // yellow
        {0,   255,   0}, // green
        {0,   255, 255}, // cyan
        {0,     0, 255}, // blue
        {128,   0, 128}  // purple
    };

    if (text.empty()) return text;

    std::ostringstream out;
    std::vector<std::string> lines;
    std::istringstream iss(text);
    for (std::string line; std::getline(iss, line);)
        lines.push_back(std::move(line));

    for (const auto& line : lines) {
        if (line.empty()) { out << '\n'; continue; }
        size_t n = line.size();
        size_t segments = colors.size() - 1;
        for (size_t i = 0; i < n; ++i) {
            float pos = n == 1 ? 0.0f : static_cast<float>(i) / (n - 1);
            float seg = pos * segments;
            size_t idx = static_cast<size_t>(seg);
            float t = seg - idx;
            if (idx >= segments) idx = segments - 1;
            RGB c = lerp(colors[idx], colors[idx + 1], t);
            out << ansi::fg(c.r, c.g, c.b) << line[i];
        }
        out << ansi::reset << '\n';
    }
    return out.str();
}

namespace fade {

    // Exactly the 17 gradients shown in the README.md (in display order)

    inline std::string purplepink(const std::string& t) { return apply_gradient(t, { 128,0,128 }, { 255,192,203 }); }
    inline std::string bluepurple(const std::string& t) { return apply_gradient(t, { 0,0,255 }, { 128,0,128 }); }
    inline std::string greenblue(const std::string& t) { return apply_gradient(t, { 0,255,0 }, { 0,0,255 }); }
    inline std::string redyellow(const std::string& t) { return apply_gradient(t, { 255,0,0 }, { 255,255,0 }); }
    inline std::string ocean(const std::string& t) { return apply_gradient(t, { 0,255,255 }, { 0,0,139 }); }
    inline std::string sunset(const std::string& t) { return apply_gradient(t, { 255,94,0 }, { 255,20,147 }); }
    inline std::string fire(const std::string& t) { return apply_gradient(t, { 255,0,0 }, { 255,215,0 }); }
    inline std::string lime(const std::string& t) { return apply_gradient(t, { 50,205,50 }, { 0,255,0 }); }
    inline std::string neon(const std::string& t) { return apply_gradient(t, { 57,255,20 }, { 255,0,255 }); }
    inline std::string peach(const std::string& t) { return apply_gradient(t, { 255,218,185 }, { 255,105,180 }); }
    inline std::string lavender(const std::string& t) { return apply_gradient(t, { 230,230,250 }, { 147,112,219 }); }
    inline std::string crimson(const std::string& t) { return apply_gradient(t, { 220,20,60 }, { 139,0,0 }); }
    inline std::string golden(const std::string& t) { return apply_gradient(t, { 255,223,0 }, { 218,165,32 }); }
    inline std::string valentine(const std::string& t) { return apply_gradient(t, { 255,20,147 }, { 255,105,180 }); }
    inline std::string aqua(const std::string& t) { return apply_gradient(t, { 0,255,255 }, { 0,191,255 }); }
    inline std::string midnight(const std::string& t) { return apply_gradient(t, { 25,25,112 }, { 0,0,139 }); }
    inline std::string rainbow(const std::string& t) { return rainbow_gradient(t); }

} // namespace fade