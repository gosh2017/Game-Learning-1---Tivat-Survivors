#include "Button.h"
#include "GameConsole.h"

#include "graphics.h"

std::unique_ptr<Button> Button::create(ButtonType type, RECT rect, LPCTSTR idle, LPCTSTR hovered,
                                       LPCTSTR pushed)
{
    std::unique_ptr<Button> res = nullptr;

    switch (type)
    {
        case ButtonType::Start:
            res = std::make_unique<StartGameButton>(rect, idle, hovered, pushed);
            break;
        case ButtonType::End:
            res = std::make_unique<EndGameButton>(rect, idle, hovered, pushed);
            break;
        default:
            break;
    }

    return res;
}

Button::Button(RECT rect, LPCTSTR idle, LPCTSTR hovered, LPCTSTR pushed)
{
    m_region = rect;
    loadimage(&m_idle, idle);
    loadimage(&m_hovered, hovered);
    loadimage(&m_pushed, pushed);
}

bool Button::checkCursorPos(int x, int y)
{
    return x >= m_region.left && x <= m_region.right && y >= m_region.top && y <= m_region.bottom;
}

void Button::draw() const
{
    switch (m_status)
    {
        case Button::Idel:
            putimage(m_region.left, m_region.top, &m_idle);
            break;
        case Button::Hovered:
            putimage(m_region.left, m_region.top, &m_hovered);
            break;
        case Button::Pushed:
            putimage(m_region.left, m_region.top, &m_pushed);
            break;
        default:
            break;
    }
}

void Button::processEvt(const ExMessage &msg)
{
    switch (msg.message)
    {
        case WM_MOUSEMOVE:
        {
            if (Idel == m_status && checkCursorPos(msg.x, msg.y))
                m_status = Hovered;
            else if (Hovered == m_status && !checkCursorPos(msg.x, msg.y))
                m_status = Idel;
        }
        break;
        case WM_LBUTTONDOWN:
            if (checkCursorPos(msg.x, msg.y)) m_status = Pushed;
            break;
        case WM_LBUTTONUP:
            if (Pushed == m_status) onClick();
            break;
        default:
            break;
    }
}

void StartGameButton::onClick()
{
    GAME_CONSOLE_INS.setGameStarted(true);

    mciSendString(_T("play bgm repeat from 0"), nullptr, 0, nullptr);
}

void EndGameButton::onClick()
{
    GAME_CONSOLE_INS.setRunning(false);
}