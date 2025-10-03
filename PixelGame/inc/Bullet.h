#pragma once
#include "Animation.h"

#include <windows.h>

class Bullet : public Animation
{
public:
    Bullet() = default;
    ~Bullet() = default;

    void draw() const;

    void update(int delta) override;

private:
    static constexpr int RADIUS = 10;
};
