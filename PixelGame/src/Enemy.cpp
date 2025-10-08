#include "Enemy.h"
#include "Bullet.h"
#include "Atlas.h"

void Enemy::initCreate(const AnimResource &res, const WindowBnd &bnd, const POINT &oriPos)
{
    Animation::initCreate(res, bnd, oriPos);
    m_shallow = Atlas::getInstance().getImage(EImageType::ShadowEnemy);
    m_shallowOffset = 20;

    ESpawnEdge edge = (ESpawnEdge)(abs(rand()) % 4);
    int winWidth = abs(bnd.rightBot.x - bnd.leftTop.x);
    int winHeight = abs(bnd.rightBot.y - bnd.leftTop.y);
    switch (edge)
    {
        case Enemy::Top:
            m_pos.x = rand() % winHeight;
            m_pos.y = -m_height;
            break;
        case Enemy::Bottom:
            m_pos.x = rand() % winHeight;
            m_pos.y = winHeight;
            break;
        case Enemy::Left:
            m_pos.x = -m_width;
            m_pos.y = rand() % winWidth;
            break;
        case Enemy::Right:
            m_pos.x = winWidth;
            m_pos.y = rand() % winWidth;
            break;
        default:
            break;
    }

    return;
}

EAnimType Enemy::getType() const
{
    return EAnimType::Enemy;
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

    if (dirX != 0) m_orientation = dirX > 0 ? EOrientation::Right : EOrientation::Left;
}