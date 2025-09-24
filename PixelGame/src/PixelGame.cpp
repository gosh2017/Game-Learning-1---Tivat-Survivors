#include "PixelGame.h"
#include "PixelGameProperty.h"
#include "Animation.h"
#include "graphics.h"

#include <windows.h>
#include <wingdi.h>

static constexpr int WIN_WIDTH = 918;
static constexpr int WIN_HEIGHT = 512;
static constexpr WindowBnd WIN_BND = {{0, 0}, {WIN_WIDTH, WIN_HEIGHT}};

void GamePixel()
{
    bool init = true;
    bool running = true;

    initgraph(WIN_WIDTH, WIN_HEIGHT);

    IMAGE background{};
    loadimage(&background, std::string(RESOURCE_PATH + _T("\\Background.png")).c_str());

    static constexpr POINT oriPlayerPos{450, 260};

    auto player = AnimFactory::create(EAnimType::Player, WIN_BND, oriPlayerPos);

    BeginBatchDraw();
    while (running)
    {
        DWORD startTime = GetTickCount();

        /* Read data. */
        ExMessage msg{};
        while (peekmessage(&msg))
        {
            player->processEvt(msg);
        }

        player->move();

        /* Draw. */
        cleardevice();

        putimage(0, 0, &background);
        player->update(1000 / 144);

        FlushBatchDraw();

        DWORD endTime = GetTickCount();
        DWORD deltaTime = endTime - startTime;
        if (deltaTime < 1000 / 144) Sleep(1000 / 144 - deltaTime);
    }

    EndBatchDraw();
}
