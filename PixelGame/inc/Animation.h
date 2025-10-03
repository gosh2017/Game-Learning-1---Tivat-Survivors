#pragma once
#include <vector>
#include <memory>
#include <windows.h>

class IMAGE;
class ExMessage;

enum class EAnimType
{
    Player,
    Enemy,
    Bullet,
};

enum class EBattleRes
{
    Draw,
    Win,
    Defeat,
};

struct AnimResource
{
    LPCTSTR path;
    int playerAnimNum;
    int interval;
};

struct WindowBnd
{
    POINT leftTop;
    POINT rightBot;
};

class Animation
{
public:
    Animation() = default;
    virtual ~Animation() = default;

    virtual void initCreate(const AnimResource &res, const WindowBnd &bnd, const POINT &oriPos);

    virtual void processEvt(const ExMessage &msg);

    virtual void move(const Animation *ref);
    virtual void update(int delta);

    virtual int getSpeed() const;

    POINT getPos() const;
    void setPos(const POINT &pos);

    EBattleRes battle(const Animation &other) const;

protected:
    virtual bool checkCollision(const Animation &other) const;

protected:
    int m_timer;
    int m_frameIdx;
    int m_intervalMs;
    POINT m_pos;
    std::vector<std::unique_ptr<IMAGE>> m_frameList;
    WindowBnd m_winBnd;

protected:
    static constexpr int m_WIDTH = 40;
    static constexpr int m_HEIGHT = 40;
};

class AnimFactory
{
public:
    AnimFactory() = delete;
    virtual ~AnimFactory() = delete;

    static std::unique_ptr<Animation> create(EAnimType type, const WindowBnd &bnd,
                                             const POINT &oriPos);
};