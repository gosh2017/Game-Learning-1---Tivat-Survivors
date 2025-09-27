#include "Bullet.h"

#include "graphics.h"

void Bullet::draw() const
{
    setlinecolor(RGB(255, 155, 50));
    setfillcolor(RGB(200, 75, 10));
    fillcircle(m_pos.x, m_pos.y, RADIUS);
}