#pragma once
#include "graphics.h"
#include <map>
#include <string>

class Sprite {
protected:
    SDL_Texture *_texture;
    std::map<std::string, SDL_Rect>_src;
public:
    Sprite();
    Sprite(SDL_Texture *texture);
    Sprite(Graphics *g, std::string file_path);
    ~Sprite();

    void SetTexture(SDL_Texture *texture);
    void SetTexture(Graphics *g, std::string file_path);

    SDL_Texture *GetTexture();

    void AddState(std::string state, int x, int y, int w, int h);

    virtual void Draw(Graphics *g, std::string state, SDL_FRect &dst, SDL_RendererFlip flip, bool offs, float angle = 0, SDL_FPoint *center = NULL);
    virtual void Draw(Graphics *g, std::string state, SDL_Rect &dst, SDL_RendererFlip flip, float angle = 0, SDL_Point *center = NULL);
};
