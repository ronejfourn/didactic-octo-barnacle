#pragma once
#include "SDL2/SDL_render.h"
#include "utils.h"

class Graphics {
    static Graphics *_instance;
private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    Vec2i _wdim;
    uint32_t _dbegin;
    Vec2f _off;
    float _dt, _ft;

    Graphics();
public:
    static Graphics *GetInstance();

    SDL_Renderer *GetRenderer();

    void Clear();
    void Update();

    Vec2i GetCurrentResolution();
    Vec2f GetCursorPosition(bool offseted = false);

    void SetTitle(const char *title, const char *icon_file = nullptr);
    void SetTargetFPS(uint32_t fps);
    void SetOffset(Vec2f offset);
    void SetOffset(float ox, float oy);

    float GetDeltaTime();

    void DrawRect(float tl_x, float tl_y, float width, float height, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255, bool offs = true);
    void FillRect(float tl_x, float tl_y, float width, float height, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255, bool offs = true);
    void DrawRect(SDL_Rect &rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
    void FillRect(SDL_Rect &rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
    void DrawRect(SDL_FRect &rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255, bool offs = true);
    void FillRect(SDL_FRect &rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255, bool offs = true);

    void DrawPoint(float x, float y, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255, bool offs = true);
    void DrawLine(float x1, float y1, float x2, float y2, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255, uint32_t t = 1, bool offs = true);

    void DrawTexture(SDL_Texture *texture, SDL_Rect &src, SDL_Rect &dst , SDL_Point *center = nullptr , float angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void DrawTexture(SDL_Texture *texture, SDL_Rect &src, SDL_FRect &dst, bool offs = true, SDL_FPoint *center = nullptr, float angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);

    SDL_Texture *LoadImage(const char *image_path);
    SDL_Texture *CreateTexture(int width, int height);
    void BindTexture(SDL_Texture *texture);
};
