#pragma once
#include "PixelGameProperty.h"

#include <unordered_map>
#include <memory>

class IMAGE;

class Atlas
{
public:
    virtual ~Atlas() = default;
    static Atlas& getInstance();
    void loadAll();
    FrameList* getFrameList(EAnimType type, EOrientation orientation);
    IMAGE* getImage(EImageType type);

private:
    Atlas() = default;
    void loadRes(EAnimType type, const AnimResource& res);
    void loadImage(EImageType type, LPCTSTR path, int width, int height);
    void reverseFrameList(const FrameList& framelist, FrameList& reversed);

private:
    std::unordered_map<EAnimType, FrameList> m_rawResource;
    std::unordered_map<EAnimType, FrameList> m_reverseResource;
    std::unordered_map<EImageType, std::unique_ptr<IMAGE>> m_images;
};