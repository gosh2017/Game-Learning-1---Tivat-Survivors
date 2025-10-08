#include "PixelGame.h"
#include "PixelGameProperty.h"
#include "Animation.h"
#include "graphics.h"

#include <windows.h>
#include <wingdi.h>

static constexpr int WIN_WIDTH = 918;
static constexpr int WIN_HEIGHT = 512;
static constexpr WindowBnd WIN_BND = {{0, 0}, {WIN_WIDTH, WIN_HEIGHT}};

void TryGenEnemy(std::vector<std::unique_ptr<Animation>> &ents)
{
    static constexpr int INTERVAL = 100;
    static int counter = 0;
    if ((++counter) % INTERVAL == 0)
        ents.push_back(AnimFactory::create(EAnimType::Enemy, WIN_BND, {}));
}

void GamePixel()
{
    bool init = true;
    bool running = true;

    initgraph(WIN_WIDTH, WIN_HEIGHT);

    IMAGE background{};
    loadimage(&background, std::string(RESOURCE_PATH + _T("\\Background.png")).c_str());

    static constexpr POINT oriPlayerPos{450, 260};

    std::vector<std::unique_ptr<Animation>> ents;
    ents.push_back(AnimFactory::create(EAnimType::Player, WIN_BND, oriPlayerPos));
    auto &player = ents[0];

    BeginBatchDraw();
    while (running)
    {
        DWORD startTime = GetTickCount();

        /* Read data. */
        ExMessage msg{};
        while (peekmessage(&msg))
        {
            ents[0]->processEvt(msg);
        }

        for (auto &ent : ents) ent->move(ents[0].get());

        TryGenEnemy(ents);

        /* Draw. */
        cleardevice();

        putimage(0, 0, &background);
        for (auto &ent : ents) ent->update(1000 / 144);

        FlushBatchDraw();

        DWORD endTime = GetTickCount();
        DWORD deltaTime = endTime - startTime;
        if (deltaTime < 1000 / 144) Sleep(1000 / 144 - deltaTime);
    }

    EndBatchDraw();
}
