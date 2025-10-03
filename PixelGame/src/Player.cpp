#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

#include "graphics.h"

void PlayerAnim::initCreate(const AnimResource &res, const WindowBnd &bnd, const POINT &oriPos)
{
    Animation::initCreate(res, bnd, oriPos);

    m_bullets.push_back(std::move(AnimFactory::create(EAnimType::Bullet, bnd, {})));
    m_bullets.push_back(std::move(AnimFactory::create(EAnimType::Bullet, bnd, {})));
    m_bullets.push_back(std::move(AnimFactory::create(EAnimType::Bullet, bnd, {})));
}

static bool isMoveUp = false;
static bool isMoveDown = false;
static bool isMoveLeft = false;
static bool isMoveRight = false;

void PlayerAnim::processEvt(const ExMessage &msg)
{
    if (msg.message == WM_KEYDOWN)
    {
        switch (msg.vkcode)
        {
            case VK_UP:
                isMoveUp = true;
                break;
            case VK_DOWN:
                isMoveDown = true;
                break;
            case VK_LEFT:
                isMoveLeft = true;
                break;
            case VK_RIGHT:
                isMoveRight = true;
                break;
            default:
                break;
        }
    }
    else if (msg.message == WM_KEYUP)
    {
        switch (msg.vkcode)
        {
            case VK_UP:
                isMoveUp = false;
                break;
            case VK_DOWN:
                isMoveDown = false;
                break;
            case VK_LEFT:
                isMoveLeft = false;
                break;
            case VK_RIGHT:
                isMoveRight = false;
                break;
            default:
                break;
        }
    }
}

int PlayerAnim::getSpeed() const
{
    static constexpr int SPEED = 5;
    return SPEED;
}

void PlayerAnim::move(const Animation *ref)
{
    int dirX = isMoveRight - isMoveLeft;
    int dirY = isMoveDown - isMoveUp;
    double lenDir = sqrt(abs(dirX) + abs(dirY));
    if (lenDir != 0)
    {
        double norX = dirX / lenDir;
        double norY = dirY / lenDir;
        m_pos.x += (int)(getSpeed() * norX);
        m_pos.y += (int)(getSpeed() * norY);
    }

    if (m_pos.x < 0) m_pos.x = 0;
    if (m_pos.y < 0) m_pos.y = 0;
    if (m_pos.x + m_WIDTH > m_winBnd.rightBot.x) m_pos.x = m_winBnd.rightBot.x - m_WIDTH;
    if (m_pos.y + m_HEIGHT > m_winBnd.rightBot.y) m_pos.y = m_winBnd.rightBot.y - m_HEIGHT;

    for (int i = 0; i < m_bullets.size(); i++)
    {
        static const double RADIAL_SPEED = 0.0045 / 2;
        static const double TANGENT_SPEED = 0.0055 / 2;

        double radianInterval = 2 * 3.14159 / m_bullets.size();
        POINT relPos = this->getPos();
        double radius = 100 + 25 * sin(GetTickCount() * RADIAL_SPEED);

        double radian = GetTickCount() * TANGENT_SPEED + radianInterval * i;

        m_bullets[i]->setPos({relPos.x + m_WIDTH / 2 + (int)(radius * sin(radian)),
                              relPos.y + m_HEIGHT / 2 + (int)(radius * cos(radian))});
    }
}

void PlayerAnim::update(int delta)
{
    Animation::update(delta);

    for (auto &bullet : m_bullets) bullet->update(delta);
}

bool PlayerAnim::checkCollision(const Animation &other) const
{
    try
    {
        dynamic_cast<const Enemy &>(other);
    }
    catch (...)
    {
        return false;
    }

    POINT checkPos = {other.getPos().x + m_WIDTH / 2, other.getPos().y + m_HEIGHT / 2};

    bool isOverlapX = getPos().x >= other.getPos().x && getPos().x <= other.getPos().x + m_WIDTH;
    bool isOverlapY = getPos().y >= other.getPos().y && getPos().y <= other.getPos().y + m_HEIGHT;

    return isOverlapX && isOverlapY;
}