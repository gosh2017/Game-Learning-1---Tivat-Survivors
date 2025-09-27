#include "Animation.h"
#include "Enemy.h"
#include "PixelGameProperty.h"

#include "graphics.h"

void PutImageAlpha(const POINT &pos, IMAGE *img)
{
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend(GetImageHDC(nullptr), pos.x, pos.y, w, h, GetImageHDC(img), 0, 0, w, h,
               {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA});
}

void Animation::initCreate(const AnimResource &res, const WindowBnd &bnd, const POINT &oriPos)
{
    m_intervalMs = res.interval;
    m_winBnd = bnd;
    m_pos = oriPos;
    for (int i = 0; i < res.playerAnimNum; i++)
    {
        m_frameList.push_back(std::make_unique<IMAGE>());
        std::string path = RESOURCE_PATH + "\\" + res.path + std::to_string(i) + ".png";
        loadimage(m_frameList[i].get(), path.c_str(), m_WIDTH, m_HEIGHT, true);
    }
}

void Animation::processEvt(const ExMessage &msg)
{
}

void Animation::move(const Animation *ref)
{
}

POINT Animation::getPos() const
{
    return m_pos;
}

void Animation::update(int delta)
{
    m_timer += delta;
    if (m_timer >= m_intervalMs)
    {
        m_frameIdx = (m_frameIdx + 1) % m_frameList.size();
        m_timer = 0;
    }

    PutImageAlpha(m_pos, m_frameList[m_frameIdx].get());
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
}

std::unique_ptr<Animation> AnimFactory::create(EAnimType type, const WindowBnd &bnd,
                                               const POINT &oriPos)
{
    std::unique_ptr<Animation> anim = nullptr;
    AnimResource res{};

    switch (type)
    {
        case EAnimType::Player:
            res = {"Charactor_", 2, 45};
            anim = std::make_unique<PlayerAnim>();
            break;
        case EAnimType::Enemy:
            res = {"Enemy_", 2, 45};
            anim = std::make_unique<Enemy>();
            break;
        default:
            break;
    }

    if (nullptr != anim) anim->initCreate(res, bnd, oriPos);

    return anim;
}