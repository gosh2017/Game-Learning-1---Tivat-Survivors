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

    void initCreate(const AnimResource &res, const WindowBnd &bnd, const POINT &oriPos);

    virtual void processEvt(const ExMessage &msg);

    virtual void move();
    void update(int delta);

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

class PlayerAnim : public Animation
{
public:
    PlayerAnim() = default;
    virtual ~PlayerAnim() = default;

    void processEvt(const ExMessage &msg) override;
    virtual void move() override;

private:
    static constexpr int m_playerSpeed = 5;
};

class AnimFactory
{
public:
    AnimFactory() = delete;
    virtual ~AnimFactory() = delete;

    static std::unique_ptr<Animation> create(EAnimType type, const WindowBnd &bnd,
                                             const POINT &oriPos);
};