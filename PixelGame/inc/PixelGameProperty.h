#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include <memory>

class IMAGE;

enum class EAnimType
{
    None,
    Player,
    Enemy,
    Bullet,
};

enum class EImageType
{
    None,
    ShadowPlayer,
    ShadowEnemy,
};

enum class EBattleRes
{
    Draw,
    Win,
    Defeat,
};

enum class EOrientation
{
    Left,
    Right,
};

struct AnimResource
{
    LPCTSTR path;
    int playerAnimNum;
    int interval;
    int width;
    int height;
};

using FrameList = std::vector<std::shared_ptr<IMAGE>>;

static std::string RESOURCE_PIXEL_PATH("Resources\\PixelAssets");