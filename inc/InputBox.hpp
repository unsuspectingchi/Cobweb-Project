#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class InputBox
{
public:
  InputBox(int fontSize, std::string fontPath, int boxWidth, int boxLeft,
           int boxTop, SDL_Color fontColor, SDL_Color inputColor);
  InputBox(int fontSize, std::string fontPath, int boxWidth, int boxLeft,
           int boxTop, SDL_Color fontColor, SDL_Color inputColor,
           void (*callback)(std::string));

  void Initialize();
  void Run(SDL_Event& event);
  void Finalize();

  void Draw(SDL_Renderer* renderer);

  void HandleKeyboard(SDL_Event& event);
  void HandleMouse(SDL_Event& event);

  std::string GetInput();
  void ResetInput();
  void UpdateText();

private:
  int fontSize;
  std::string fontPath;
  int boxWidth;
  int boxLeft;
  int boxTop;
  SDL_Color fontColor;
  SDL_Color inputColor;
  void (*callback)(std::string);

  TTF_Font* font;
  SDL_Texture* visualText;

  SDL_Rect textRect;
  SDL_Rect textContainer;

  std::string input;

  bool inputSelected = false;
  bool hasCallback;
};