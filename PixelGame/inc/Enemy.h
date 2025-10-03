#pragma once
#include "Animation.h"

class Bullet;

class Enemy : public Animation
{
public:
    enum ESpawnEdge
    {
        Top = 0,
        Bottom,
        Left,
        Right,
    };

public:
    Enemy() = default;
    virtual ~Enemy() = default;

    void initCreate(const AnimResource &res, const WindowBnd &bnd, const POINT &oriPos) override;

    int getSpeed() const override;

    void move(const Animation *ref) override;

    bool checkCollision(const Animation &bullet) const override;
};
