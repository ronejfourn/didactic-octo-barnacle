#include "headers/ui.h"
#include <SDL2/SDL.h>

extern SDL_Texture *singleTexture;

UI *UI::_instance = nullptr;

std::string menuItems[] = {"Play", "Options", "Exit"};
std::string optionsItems[] = {"Back", "Something"};
std::string pauseMenuItems[] = {"Resume", "Restart", "Menu", "Save"};

UI::UI(){
    _currentState = GameState::MENU;
}

UI *UI::GetInstance(){
    if(!_instance) _instance = new UI;
    return _instance;
}

UI::~UI(){}

void UI::LoadFont(Graphics *g) {
    _fontTexture = g->LoadImage("../../res/font.png");
    
    _charDim = {14, 18};
    for(int i = 0; i < 95; ++i) {
        _charCoords[i].x = (i % _charDim.y) * _charDim.x;
        _charCoords[i].y = (i / _charDim.y) * _charDim.y;
    }
}

GameState UI::GetCurrentState(){
    return _currentState;
}

void UI::SetState(GameState state){
    _currentState = state;
    _selectedOptionIndex = 0;
}

void UI::Pause(){
    if(_currentState == GameState::PAUSE)
        SetState(GameState::ALIVE);
    else
        SetState(GameState::PAUSE);
}

void UI::ChangeOption(bool up){
    uint8_t max;
    if(_currentState == GameState::MENU)
        max = 2;
    else if(_currentState == GameState::OPTIONS)
        max = 1;
    else if(_currentState == GameState::PAUSE)
        max = 3;
    if(up)
        _selectedOptionIndex = _selectedOptionIndex ? _selectedOptionIndex - 1 : max;
    else
        _selectedOptionIndex = (_selectedOptionIndex == max) ? 0 : _selectedOptionIndex + 1;
}

void UI::ChooseOption(bool *restart){
    if(_currentState == GameState::MENU){
        if(_selectedOptionIndex == 0)
            SetState(GameState::ALIVE);
        else if(_selectedOptionIndex == 1)
            SetState(GameState::OPTIONS);
        else if(_selectedOptionIndex == 2){
            SDL_Event e;
            e.type = SDL_QUIT;
            SDL_PushEvent(&e);
        }
    } else if(_currentState == GameState::OPTIONS){
        if(_selectedOptionIndex == 0)
            SetState(GameState::MENU);
    } else if(_currentState == GameState::PAUSE){
        if(_selectedOptionIndex == 0)
            SetState(GameState::ALIVE);
        else if(_selectedOptionIndex == 1){
            SetState(GameState::ALIVE);
            *restart = true;
        } else if(_selectedOptionIndex == 2){
            SetState(GameState::MENU);
            *restart = true;
        }
    }
}


void UI::DisplayText(Graphics *g, std::string msg, SDL_Rect dst, uint16_t ftSize){
    const char *msgStr = msg.c_str();
    uint16_t txtSize = msg.size();

    SDL_Rect chrDst;
    chrDst.x = dst.x;
    chrDst.y = dst.y;
    chrDst.h = dst.h < ftSize ? dst.h : ftSize;
    chrDst.w = fontRatio * chrDst.h;

    if((dst.h / float(chrDst.h)) * (dst.w / float(chrDst.w)) < txtSize){
        Logger::LogWarning(("Following message does not fit in the box. Characters will be squished: " + msg).c_str());
        chrDst.w = ((dst.h / chrDst.h) * dst.w) / msg.size();
    }

    if(txtSize * chrDst.w < dst.w)
        chrDst.x += (dst.w - (txtSize * chrDst.w)) / 2;
    for(int i = 0; i < txtSize; i++){
        if(chrDst.x >= dst.x + dst.w){
            chrDst.y += chrDst.h;
            chrDst.x = dst.x;
            if((txtSize - i) * chrDst.w < dst.w)
                chrDst.x += (dst.w - ((txtSize - i) * chrDst.w)) / 2;
        }
        SDL_Rect src = {_charCoords[msgStr[i] - 32].x, _charCoords[msgStr[i] - 32].y, _charDim.x, _charDim.y};
        g->DrawTexture(_fontTexture, src, chrDst);
        chrDst.x += chrDst.w;
    }
}

void UI::DisplayInfo(Graphics *g, Player &p){
    float hp = p.GetHp();
    SDL_Rect src = {0, 256, 16, 16};
    src.x = 288 * (hp >= 75) + 304 * (hp < 75 && hp >=25) + 320 * (hp < 25);

    SDL_Rect healthDst = {0, 0, int(src.w * 1.5), int(src.h * 1.5)};
    g->DrawTexture(singleTexture, src, healthDst);

    healthDst.x += healthDst.w;
    healthDst.w = 120;
    DisplayText(g, "HP:" + std::to_string(int(hp)), healthDst, healthDst.h );
}

void UI::DrawMenu(Graphics *g){
    Vec2i windowSize = g->GetLogicalResolution();
    SDL_Rect menuBox = {0, 0, windowSize.x / 4, windowSize.y / 4};
    menuBox.x = (windowSize.x - menuBox.w) / 2;
    menuBox.y = (windowSize.y - menuBox.h) / 2;
    menuBox.h /= 3;

    uint16_t ftSize = 35;
    for(const auto &i : menuItems){
        DisplayText(g, i, menuBox, i == menuItems[_selectedOptionIndex] ? 40 : ftSize);
        menuBox.y += menuBox.h;
    }
}

void UI::DrawOptions(Graphics *g){
    Vec2i windowSize = g->GetLogicalResolution();
    SDL_Rect optionsBox = {0, 0, windowSize.x / 4, windowSize.y / 4};
    optionsBox.x = (windowSize.x - optionsBox.w) / 2;
    optionsBox.y = (windowSize.y - optionsBox.h) / 2;
    optionsBox.h /= 2;

    uint16_t ftSize = 28;
    for(const auto &i : optionsItems){
        DisplayText(g, i, optionsBox, i == optionsItems[_selectedOptionIndex] ? 35 : ftSize);
        optionsBox.y += optionsBox.h;
    }
}

void UI::DrawPauseMenu(Graphics *g){
    Vec2i windowSize = g->GetLogicalResolution();
    SDL_Rect container = {0, 0, windowSize.x / 4, windowSize.y / 4};
    container.x = (windowSize.x - container.w) / 2;
    container.y = (windowSize.y - container.h) / 2;
    g->FillRect(container, 25, 25, 25, 200);
    
    container.h /= 4;
    uint16_t ftSize = 28;
    for(const auto &i : pauseMenuItems){
        DisplayText(g, i, container, i == pauseMenuItems[_selectedOptionIndex] ? 35 : ftSize);
        container.y += container.h;
    }
}

void UI::Draw(Graphics *g, Player &p){
    if(_currentState == GameState::ALIVE)
        DisplayInfo(g, p);
    else if(_currentState == GameState::MENU)
        DrawMenu(g);
    else if(_currentState == GameState::OPTIONS)
        DrawOptions(g);
    else if(_currentState == GameState::PAUSE)
        DrawPauseMenu(g);
}
