#include "InputBox.hpp"

InputBox::InputBox(int fontSize, std::string fontPath, int boxWidth,
                   int boxLeft, int boxTop, SDL_Color fontColor,
                   SDL_Color inputColor)
    : fontSize(fontSize), fontPath(fontPath), boxWidth(boxWidth),
      boxLeft(boxLeft), boxTop(boxTop), fontColor(fontColor),
      inputColor(inputColor), hasCallback(false)
{
}

InputBox::InputBox(int fontSize, std::string fontPath, int boxWidth,
                   int boxLeft, int boxTop, SDL_Color fontColor,
                   SDL_Color inputColor, void (*callback)(std::string))
    : fontSize(fontSize), fontPath(fontPath), boxWidth(boxWidth),
      boxLeft(boxLeft), boxTop(boxTop), fontColor(fontColor),
      inputColor(inputColor), callback(callback), hasCallback(true)
{
}

void InputBox::Draw(SDL_Renderer* renderer)
{
  SDL_Surface* textSurface =
      TTF_RenderText_Blended(font, input.c_str(), fontColor);
  visualText = SDL_CreateTextureFromSurface(renderer, textSurface);

  SDL_FreeSurface(textSurface);
  textSurface = NULL;

  SDL_SetRenderDrawColor(renderer, inputColor.r, inputColor.g, inputColor.b,
                         inputColor.a);
  SDL_RenderFillRect(renderer, &textRect);

  SDL_RenderCopy(renderer, visualText, NULL, &textContainer);
}

void InputBox::Finalize()
{
  SDL_DestroyTexture(visualText);
  TTF_CloseFont(font);
}

std::string InputBox::GetInput() { return input; }

void InputBox::HandleKeyboard(SDL_Event& event)
{
  if (!inputSelected)
  {
    return;
  }
  if (event.key.keysym.sym == SDLK_BACKSPACE)
  {
    if (input.length() > 0)
    {
      input.pop_back();
    }
    UpdateText();
    return;
  }
  if (event.key.keysym.sym == SDLK_RETURN && hasCallback && input.length() > 0)
  {
    callback(input);
    ResetInput();
    UpdateText();
  }
  if (event.key.keysym.sym < SDLK_0 || event.key.keysym.sym > SDLK_9)
  {
    return;
  }

  input.append(1, (char)event.key.keysym.sym);
  UpdateText();
}

void InputBox::HandleMouse(SDL_Event& event)
{
  SDL_Point p = {.x = event.motion.x, .y = event.motion.y};

  if (SDL_PointInRect(&p, &textRect))
  {
    if (!inputSelected)
    {
      inputSelected = true;
    }
  }
  else
  {
    inputSelected = false;
  }
}

void InputBox::Initialize()
{
  font = TTF_OpenFont(fontPath.c_str(), fontSize);

  textRect.x = boxLeft;
  textRect.y = boxTop;
  textRect.w = boxWidth;
  textContainer.x = boxLeft;
  textContainer.y = boxTop;

  int unitHeight;
  int unitWidth; // width not used
  TTF_SizeText(font, "m", &unitWidth, &unitHeight);

  textRect.h = unitHeight;
  textContainer.h = unitHeight;
}

void InputBox::ResetInput() { input = ""; }

void InputBox::Run(SDL_Event& event)
{
  if (event.type == SDL_KEYDOWN)
  {
    HandleKeyboard(event);
  }
  else if (event.type == SDL_MOUSEBUTTONDOWN)
  {
    HandleMouse(event);
  }
}

void InputBox::UpdateText()
{
  int w, h;
  TTF_SizeText(font, input.c_str(), &w, &h);
  if (w < boxWidth)
  {
    textContainer.w = w;
  }
}