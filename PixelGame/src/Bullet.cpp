#include "Bullet.h"

#include "graphics.h"

EAnimType Bullet::getType() const
{
    return EAnimType::Bullet;
}

void Bullet::draw() const
{
    setlinecolor(RGB(255, 155, 50));
    setfillcolor(RGB(200, 75, 10));
    fillcircle(m_pos.x, m_pos.y, RADIUS);
}

void Bullet::update(int delta)
{
    draw();
}