#pragma once

#ifdef _WIN32
#ifdef ANIM_EXPORTS
#define ANIM_API __declspec(dllexport)
#else
#define ANIM_API __declspec(dllimport)
#endif
#else
#define ANIM_API
#endif

ANIM_API void GamePixel();
