#include "Animation.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Atlas.h"

#include "graphics.h"

void PutImageAlpha(const POINT &pos, IMAGE *img)
{
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend(GetImageHDC(nullptr), pos.x, pos.y, w, h, GetImageHDC(img), 0, 0, w, h,
               {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA});
}

EAnimType Animation::getType() const
{
    return EAnimType::None;
}

void Animation::initCreate(const AnimResource &res, const WindowBnd &bnd, const POINT &oriPos)
{
    m_intervalMs = res.interval;
    m_winBnd = bnd;
    m_pos = oriPos;
    m_width = res.width;
    m_height = res.height;
    m_leftFrameList = Atlas::getInstance().getFrameList(getType(), EOrientation::Left);
    m_rightFrameList = Atlas::getInstance().getFrameList(getType(), EOrientation::Right);
}

void Animation::processEvt(const ExMessage &msg)
{
}

void Animation::move(const Animation *ref)
{
}

int Animation::getSpeed() const
{
    return 5;
}

POINT Animation::getPos() const
{
    return m_pos;
}

void Animation::setPos(const POINT &pos)
{
    m_pos = pos;
}

EBattleRes Animation::battle(const Animation &other) const
{
    return EBattleRes::Draw;
}

void Animation::hurt()
{
    m_alive = false;
}

bool Animation::isAlive()
{
    return m_alive;
}

void Animation::update(int delta)
{
    // static constexpr int SHALLOW_WIDTH = 32;
    POINT shallowPos{};
    shallowPos.x = getPos().x + (m_width / 2 - m_shallow->getwidth() / 2);
    shallowPos.y = getPos().y + m_height - m_shallowOffset;
    PutImageAlpha(shallowPos, m_shallow);

    const FrameList *frameList = m_leftFrameList;
    if (EOrientation::Left == m_orientation)
        frameList = m_leftFrameList;
    else if (EOrientation::Right == m_orientation)
        frameList = m_rightFrameList;

    m_timer += delta;
    if (m_timer >= m_intervalMs)
    {
        m_frameIdx = (m_frameIdx + 1) % frameList->size();
        m_timer = 0;
    }

    PutImageAlpha(m_pos, (*frameList)[m_frameIdx].get());
}

std::unique_ptr<Animation> AnimFactory::create(EAnimType type, const WindowBnd &bnd,
                                               const POINT &oriPos)
{
    std::unique_ptr<Animation> anim = nullptr;
    AnimResource res{};

    switch (type)
    {
        case EAnimType::Player:
            res = {"", 6, 45, 50, 50};
            anim = std::make_unique<PlayerAnim>();
            break;
        case EAnimType::Enemy:
            res = {"", 6, 45, 50, 50};
            anim = std::make_unique<Enemy>();
            break;
        case EAnimType::Bullet:
            res = {"", 1, 45};
            anim = std::make_unique<Bullet>();
            break;
        default:
            break;
    }

    if (nullptr != anim) anim->initCreate(res, bnd, oriPos);

    return anim;
}