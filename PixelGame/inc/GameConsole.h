#pragma once
#include "PixelGameProperty.h"

#include <unordered_map>
#include <memory>

class IMAGE;
class Animation;
class Button;
class ExMessage;

class GameConsole
{
public:
    static GameConsole& getInstance();

    void init();
    void loadMus();
    void loadMenu();
    void showMenu();
    void processMenu(const ExMessage& msg);

    void drawPlayerScore() const;
    void tryGenEnemy(std::vector<std::unique_ptr<Animation>>& ents);

    Animation* player();

    bool isGameStarted() const;
    void setGameStarted(bool started);

    bool isRunning() const;
    void setRunning(bool running);

    int getScore() const;
    void setScore(int score);

    void reset();

private:
    GameConsole() = default;
    virtual ~GameConsole() = default;

private:
    bool m_isGameStarted = false;
    bool m_running = true;
    int m_score = 0;
    std::unique_ptr<Animation> m_player;
    std::vector<std::unique_ptr<Button>> m_btns;
    std::unique_ptr<IMAGE> m_menu;
};

#define GAME_CONSOLE_INS GameConsole::getInstance()