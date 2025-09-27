#pragma once
#include <windows.h>

class Bullet
{
public:
    Bullet() = default;
    ~Bullet() = default;

    void draw() const;

private:
    static constexpr int RADIUS = 10;

private:
    POINT m_pos;
};