#include "Animation.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
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

int Animation::getSpeed() const
{
    return 5;
}

bool Animation::checkCollision(const Animation &other) const
{
    return false;
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
    EBattleRes res = EBattleRes::Draw;
    if (checkCollision(other)) res = EBattleRes::Defeat;

    return res;
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