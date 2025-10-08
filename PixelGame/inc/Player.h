#pragma once
#include "Animation.h"

class Bullet;

class PlayerAnim : public Animation
{
public:
    PlayerAnim() = default;
    virtual ~PlayerAnim() = default;

    void initCreate(const AnimResource &res, const WindowBnd &bnd, const POINT &oriPos) override;
    EAnimType getType() const override;

    void processEvt(const ExMessage &msg) override;
    void move(const Animation *ref) override;
    int getSpeed() const override;
    EBattleRes battle(const Animation &other) const override;
    void update(int delta) override;
    bool checkCollisionBullet(const Animation &other) const;
    bool checkCollisionSelf(const Animation &other) const;

private:
    std::vector<std::unique_ptr<Animation>> m_bullets;
};