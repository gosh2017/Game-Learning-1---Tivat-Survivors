#include "Enemy.h"
#include "Bullet.h"

void Enemy::initCreate(const AnimResource &res, const WindowBnd &bnd, const POINT &oriPos)
{
    Animation::initCreate(res, bnd, oriPos);

    ESpawnEdge edge = (ESpawnEdge)(rand() % 4);
    int winHeight = abs(bnd.rightBot.x - bnd.leftTop.x);
    int winWidth = abs(bnd.rightBot.y - bnd.leftTop.y);
    switch (edge)
    {
        case Enemy::Top:
            m_pos.x = rand() % winHeight;
            m_pos.y = -m_HEIGHT;
            break;
        case Enemy::Bottom:
            m_pos.x = rand() % winHeight;
            m_pos.y = winHeight;
            break;
        case Enemy::Left:
            m_pos.x = -m_WIDTH;
            m_pos.y = rand() % winWidth;
            break;
        case Enemy::Right:
            m_pos.x = winWidth;
            m_pos.y = rand() % winWidth;
            break;
        default:
            break;
    }
}

int Enemy::getSpeed() const
{
    static constexpr int SPEED = 2;
    return SPEED;
}

void Enemy::move(const Animation *ref)
{
    if (nullptr == ref) return;

    POINT refPos = ref->getPos();
    int dirX = refPos.x - m_pos.x;
    int dirY = refPos.y - m_pos.y;
    double lenDir = sqrt(pow(dirX, 2) + pow(dirY, 2));
    if (lenDir != 0)
    {
        double norX = dirX / lenDir;
        double norY = dirY / lenDir;
        m_pos.x += (int)(getSpeed() * norX);
        m_pos.y += (int)(getSpeed() * norY);
    }
}

bool Enemy::checkCollision(const Animation &bullet) const
{
    try
    {
        dynamic_cast<const Bullet &>(bullet);
    }
    catch (...)
    {
        return false;
    }

    bool isOverlapX =
        bullet.getPos().x >= this->getPos().x && bullet.getPos().x <= this->getPos().x + m_WIDTH;
    bool isOverlapY =
        bullet.getPos().y >= this->getPos().y && bullet.getPos().y <= this->getPos().y + m_HEIGHT;

    return isOverlapX && isOverlapY;
}