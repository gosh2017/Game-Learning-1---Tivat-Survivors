#pragma once
#include "graphics.h"

#include <memory>

class ExMessage;

enum class ButtonType
{
    Start,
    End,
};

class Button
{
public:
    static std::unique_ptr<Button> create(ButtonType type, RECT rect, LPCTSTR idle, LPCTSTR hovered,
                                          LPCTSTR pushed);

public:
    Button(RECT rect, LPCTSTR idle, LPCTSTR hovered, LPCTSTR pushed);
    virtual ~Button() = default;

public:
    void draw() const;
    void processEvt(const ExMessage &msg);

protected:
    virtual void onClick() = 0;

private:
    enum Status
    {
        Idel,
        Hovered,
        Pushed,
    };

    bool checkCursorPos(int x, int y);

private:
    RECT m_region;
    IMAGE m_idle;
    IMAGE m_hovered;
    IMAGE m_pushed;
    Status m_status = Idel;
};

class StartGameButton : public Button
{
public:
    StartGameButton(RECT rect, LPCTSTR idle, LPCTSTR hovered, LPCTSTR pushed)
        : Button(rect, idle, hovered, pushed) {};
    virtual ~StartGameButton() = default;

    void onClick() override;
};

class EndGameButton : public Button
{
public:
    EndGameButton(RECT rect, LPCTSTR idle, LPCTSTR hovered, LPCTSTR pushed)
        : Button(rect, idle, hovered, pushed) {};
    virtual ~EndGameButton() = default;

    void onClick() override;
};
