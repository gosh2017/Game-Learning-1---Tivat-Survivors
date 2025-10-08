#include "PixelGame.h"
#include "PixelGameProperty.h"
#include "GameConsole.h"
#include "Animation.h"
#include "Atlas.h"
#include "graphics.h"

#include <windows.h>
#include <wingdi.h>
#include <mmsystem.h>

void GamePixel()
{
    GAME_CONSOLE_INS.init();

    IMAGE background{};
    loadimage(&background, std::string(RESOURCE_PIXEL_PATH + _T("\\Background.png")).c_str());

    std::vector<std::unique_ptr<Animation>> ents;
    auto player = GAME_CONSOLE_INS.player();

    BeginBatchDraw();
    while (GAME_CONSOLE_INS.isRunning())
    {
        DWORD startTime = GetTickCount();

        /* Read data. */
        ExMessage msg{};
        while (peekmessage(&msg))
        {
            GAME_CONSOLE_INS.processMenu(msg);
        }

        if (GAME_CONSOLE_INS.isGameStarted())
        {
            GAME_CONSOLE_INS.tryGenEnemy(ents);

            player->move(nullptr);
            for (auto &ent : ents) ent->move(player);

            for (auto &ent : ents)
            {
                EBattleRes res = player->battle(*ent);
                if (res == EBattleRes::Defeat)
                {
                    TCHAR text[128];
                    _stprintf_s(text, _T("玩家最终得分：%d ！"), GAME_CONSOLE_INS.getScore());
                    MessageBox(GetHWnd(), text, _T("游戏结束"), MB_OK);
                    GAME_CONSOLE_INS.setRunning(false);
                    break;
                }
                else if (res == EBattleRes::Win)
                {
                    ent->hurt();
                    mciSendString(_T("play hit from 0"), nullptr, 0, nullptr);
                }
            }

            for (int i = 0; i < ents.size(); i++)
            {
                if (!ents[i]->isAlive())
                {
                    std::swap(ents[i], ents.back());
                    ents.pop_back();
                    GAME_CONSOLE_INS.setScore(GAME_CONSOLE_INS.getScore() + 1);
                }
            }
        }

        /* Draw. */
        cleardevice();

        if (GAME_CONSOLE_INS.isGameStarted())
        {
            putimage(0, 0, &background);
            player->update(1000 / 144);
            for (auto &ent : ents) ent->update(1000 / 144);

            GAME_CONSOLE_INS.drawPlayerScore();
        }
        else
        {
            GAME_CONSOLE_INS.showMenu();
        }

        FlushBatchDraw();

        DWORD endTime = GetTickCount();
        DWORD deltaTime = endTime - startTime;
        if (deltaTime < 1000 / 144) Sleep(1000 / 144 - deltaTime);
    }

    EndBatchDraw();
}
