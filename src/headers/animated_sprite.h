#include "sprite.h"

class AnimatedSprite : public Sprite {
private:
    uint32_t _currentframe;
    float _elapsedtime;
    float _frametime;
    std::map<std::string, uint32_t> _framecount;
public:
    AnimatedSprite();
    AnimatedSprite(SDL_Texture *texture);
    AnimatedSprite(Graphics *g, std::string file_path);
    ~AnimatedSprite();

    uint32_t GetFPS();

    void SetFPS(uint32_t fps);
    void AddAnimation(std::string state, int x, int y, int w, int h, uint32_t frameCount = 1);

    void Animate(float deltatime, std::string state);
    void Draw(Graphics *g, std::string state, SDL_FRect &dst, SDL_RendererFlip flip, float angle = 0, SDL_FPoint *center = NULL);
    void Draw(Graphics *g, std::string state, SDL_Rect &dst , SDL_RendererFlip flip, float angle = 0, SDL_Point  *center = NULL);
};
