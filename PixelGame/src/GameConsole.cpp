#include "GameConsole.h"
#include "Animation.h"
#include "Player.h"
#include "Atlas.h"
#include "Button.h"

#include "graphics.h"

static constexpr int WIN_WIDTH = 1280;
static constexpr int WIN_HEIGHT = 720;
static constexpr WindowBnd WIN_BND = {{0, 0}, {WIN_WIDTH, WIN_HEIGHT}};

GameConsole& GameConsole::getInstance()
{
    static GameConsole ins{};
    return ins;
}

bool GameConsole::isGameStarted() const
{
    return m_isGameStarted;
}

void GameConsole::setGameStarted(bool started)
{
    m_isGameStarted = started;
}

bool GameConsole::isRunning() const
{
    return m_running;
}

void GameConsole::setRunning(bool running)
{
    m_running = running;
}

int GameConsole::getScore() const
{
    return m_score;
}
void GameConsole::setScore(int score)
{
    m_score = score;
}

Animation* GameConsole::player()
{
    return m_player.get();
}

void GameConsole::reset()
{
    m_isGameStarted = false;
    m_running = true;
    m_score = 0;
    m_player.reset();
}

void GameConsole::drawPlayerScore() const
{
    static TCHAR text[128];
    _stprintf_s(text, _T("当前玩家得分：%d"), getScore());

    setbkmode(TRANSPARENT);
    settextcolor(RGB(255, 85, 185));
    outtextxy(10, 10, text);
}

void GameConsole::tryGenEnemy(std::vector<std::unique_ptr<Animation>>& ents)
{
    static constexpr int INTERVAL = 100;
    static int counter = 0;
    if ((++counter) % INTERVAL == 0)
        ents.push_back(AnimFactory::create(EAnimType::Enemy, WIN_BND, {}));
}

void GameConsole::loadMus()
{
    mciSendString(_T("open Resources/Mus/bgm.mp3 alias bgm"), nullptr, 0, nullptr);
    mciSendString(_T("open Resources/Mus/hit.wav alias hit"), nullptr, 0, nullptr);
}

void GameConsole::loadMenu()
{
    static constexpr int BUTTON_WIDTH = 192;
    static constexpr int BUTTON_HEIGHT = 75;

    RECT startGameBtn{}, quitGameBtn{};
    startGameBtn.left = (WIN_WIDTH - BUTTON_WIDTH) / 2;
    startGameBtn.right = startGameBtn.left + BUTTON_WIDTH;
    startGameBtn.top = 430;
    startGameBtn.bottom = startGameBtn.top + BUTTON_HEIGHT;

    quitGameBtn.left = (WIN_WIDTH - BUTTON_WIDTH) / 2;
    quitGameBtn.right = quitGameBtn.left + BUTTON_WIDTH;
    quitGameBtn.top = 550;
    quitGameBtn.bottom = quitGameBtn.top + BUTTON_HEIGHT;

    m_btns.push_back(std::move(Button::create(ButtonType::Start, startGameBtn,
                                              _T("Resources/PixelAssets/ui_start_idle.png"),
                                              _T("Resources/PixelAssets/ui_start_hovered.png"),
                                              _T("Resources/PixelAssets/ui_start_pushed.png"))));
    m_btns.push_back(std::move(Button::create(ButtonType::End, quitGameBtn,
                                              _T("Resources/PixelAssets/ui_quit_idle.png"),
                                              _T("Resources/PixelAssets/ui_quit_hovered.png"),
                                              _T("Resources/PixelAssets/ui_quit_pushed.png"))));

    m_menu = std::make_unique<IMAGE>();
    loadimage(m_menu.get(), std::string(RESOURCE_PIXEL_PATH + _T("\\menu.png")).c_str());
}

void GameConsole::showMenu()
{
    putimage(0, 0, m_menu.get());
    for (auto& btn : m_btns) btn->draw();
}

void GameConsole::processMenu(const ExMessage& msg)
{
    if (isGameStarted())
        m_player->processEvt(msg);
    else
        for (auto& btn : m_btns) btn->processEvt(msg);
}

void GameConsole::init()
{
    Atlas::getInstance().loadAll();

    static constexpr POINT oriPlayerPos{450, 260};
    m_player = std::move(AnimFactory::create(EAnimType::Player, WIN_BND, oriPlayerPos));

    initgraph(WIN_WIDTH, WIN_HEIGHT);
    loadMus();
    loadMenu();
}