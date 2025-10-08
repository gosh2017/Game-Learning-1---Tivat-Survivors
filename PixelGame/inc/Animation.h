#pragma once
#include "PixelGameProperty.h"

class ExMessage;

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

    virtual EAnimType getType() const;

    virtual void processEvt(const ExMessage &msg);

    virtual void move(const Animation *ref);
    virtual void update(int delta);

    virtual int getSpeed() const;

    POINT getPos() const;
    void setPos(const POINT &pos);

    virtual EBattleRes battle(const Animation &other) const;

    void hurt();
    bool isAlive();

protected:
    int m_timer;
    int m_frameIdx;
    int m_intervalMs;
    POINT m_pos;
    FrameList *m_leftFrameList = nullptr;
    FrameList *m_rightFrameList = nullptr;
    IMAGE *m_shallow = nullptr;
    int m_shallowOffset = 8;
    WindowBnd m_winBnd;
    bool m_alive = true;
    EOrientation m_orientation = EOrientation::Left;

protected:
    int m_width = 50;
    int m_height = 50;
};

class AnimFactory
{
public:
    AnimFactory() = delete;
    virtual ~AnimFactory() = delete;

    static std::unique_ptr<Animation> create(EAnimType type, const WindowBnd &bnd,
                                             const POINT &oriPos);
};