#include "sprite.h"

Sprite::Sprite() {}

Sprite::~Sprite() {}

Sprite::Sprite(SDL_Texture *texture) {
    _texture = texture;
}

Sprite::Sprite(Graphics &g, std::string file_path) {
    _texture = g.LoadImage(file_path.c_str());
}

void Sprite::SetTexture(SDL_Texture *texture) {
    _texture = texture;
}

void Sprite::SetTexture(Graphics &g, std::string file_path) {
    _texture = g.LoadImage(file_path.c_str());
}

void Sprite::AddState(std::string state, int x, int y, int w, int h) {
    _src[state] = {x, y, w, h};
}

void Sprite::Draw(Graphics &g, std::string state, SDL_Rect *dst, Facing face, float angle, SDL_Point *center) {
    g.DrawTexture(_texture, &_src[state],
            dst, center, angle,
            face == Facing::LEFT);
}