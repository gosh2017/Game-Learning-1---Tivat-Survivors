#include "Atlas.h"

#include "graphics.h"

Atlas& Atlas::getInstance()
{
    static Atlas ins{};
    return ins;
}

void Atlas::loadRes(EAnimType type, const AnimResource& res)
{
    if (m_rawResource.end() == m_rawResource.find(type)) m_rawResource[type] = {};

    for (int i = 0; i < res.playerAnimNum; i++)
    {
        m_rawResource[type].push_back(std::make_shared<IMAGE>());
        std::string path = RESOURCE_PIXEL_PATH + "\\" + res.path + std::to_string(i) + ".png";
        loadimage(m_rawResource[type][i].get(), path.c_str(), res.width, res.height, true);
    }

    m_reverseResource[type] = {};
    reverseFrameList(m_rawResource[type], m_reverseResource[type]);
}

void Atlas::reverseFrameList(const FrameList& framelist, FrameList& reversed)
{
    for (int i = 0; i < framelist.size(); i++)
    {
        reversed.push_back(std::make_shared<IMAGE>());
        int width = framelist[i]->getwidth();
        int height = framelist[i]->getheight();
        Resize(reversed[i].get(), width, height);

        DWORD* bufferRaw = GetImageBuffer(framelist[i].get());
        DWORD* bufferReversed = GetImageBuffer(reversed[i].get());
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                int idxRaw = y * width + x;
                int idxReversed = y * width + (width - x - 1);
                bufferReversed[idxReversed] = bufferRaw[idxRaw];
            }
        }
    }
}

void Atlas::loadImage(EImageType type, LPCTSTR path, int width, int height)
{
    if (m_images.end() == m_images.find(type)) m_images[type] = {};

    auto image = std::make_unique<IMAGE>();
    loadimage(image.get(), path, width, height);
    m_images[type] = std::move(image);
}

void Atlas::loadAll()
{
    AnimResource res = {"Charactor_", 6, 45, 50, 50};
    loadRes(EAnimType::Player, res);

    res = {"Enemy_", 6, 45, 50, 50};
    loadRes(EAnimType::Enemy, res);

    loadImage(EImageType::ShadowPlayer, _T("Resources/PixelAssets/shadow_player_1.png"), 32, 20);
    loadImage(EImageType::ShadowEnemy, _T("Resources/PixelAssets/shadow_enemy_1.png"), 32, 20);
}

FrameList* Atlas::getFrameList(EAnimType type, EOrientation orientation)
{
    std::unordered_map<EAnimType, FrameList>* resource = &m_rawResource;
    if (EOrientation::Left == orientation)
        resource = &m_rawResource;
    else if (EOrientation::Right == orientation)
        resource = &m_reverseResource;

    if (resource->end() == resource->find(type))
        return nullptr;
    else
        return &((*resource)[type]);
}

IMAGE* Atlas::getImage(EImageType type)
{
    if (m_images.end() == m_images.find(type))
        return nullptr;
    else
        return m_images[type].get();
}
