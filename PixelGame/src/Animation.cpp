#include "Animation.h"
#include "graphics.h"

void GamePixel()
{
    bool init = true;
    bool running = true;

    initgraph(918, 512);
    char exePath[MAX_PATH] = {0};
    GetModuleFileName(NULL, exePath, MAX_PATH);
    SetCurrentDirectory(exePath);

    IMAGE background;
    loadimage(&background, _T("resources\\PixelAssets\\Background.png"));

    BeginBatchDraw();
    while (running)
    {
        DWORD startTime = GetTickCount();

        /* Read data. */
        ExMessage msg{};
        while (peekmessage(&msg))
        {
            if (msg.message == WM_LBUTTONDOWN)
            {
            }
        }

        /* Draw. */
        cleardevice();

        putimage(0, 0, &background);

        FlushBatchDraw();

        DWORD endTime = GetTickCount();
        DWORD deltaTime = endTime - startTime;
        if (deltaTime < 1000 / 60)
            Sleep(1000 / 60 - deltaTime);
    }

    EndBatchDraw();
}
