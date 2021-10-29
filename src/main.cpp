#include "InputBox.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <printf.h>
#include <string>

SDL_Window* _window;
SDL_Renderer* _renderer;

// Window size
int _width = 1080;
int _height = 720;

SDL_bool loop = SDL_TRUE;

InputBox* inputBox1;
InputBox* inputBox2;
InputBox* inputBox3;

// SDL_Texture* _image;

// Mix_Music* _music = NULL;

void init_sdl()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    printf("[Error] SDL Init : %s \n", SDL_GetError());
  }
  else
  {
    printf("SDL INITIALISED\n");
    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);

    printf("Display mode is %dx%dpx @ %dhz\n", dm.w, dm.h, dm.refresh_rate);
  }
}

void init_window_and_renderer()
{
  if (SDL_CreateWindowAndRenderer(_width, _height, SDL_WINDOW_SHOWN, &_window,
                                  &_renderer) != 0)
  {
    printf("[Error] Creating Window and Renderer: %s\n", SDL_GetError());
    exit(0);
  }
  else
  {
    printf("Created Window and Renderer %dx%d\n", _width, _height);
  }
}

void init_ttf() { TTF_Init(); }

void main_loop()
{
  SDL_Event event;

  while (loop)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        loop = SDL_FALSE;
      }
      inputBox1->Run(event);
      inputBox2->Run(event);
      inputBox3->Run(event);
    }
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
    SDL_RenderClear(_renderer);

    inputBox1->Draw(_renderer);
    inputBox2->Draw(_renderer);
    inputBox3->Draw(_renderer);

    SDL_RenderPresent(_renderer);
    SDL_Delay(10);
  }
}

void log(std::string msg) { std::cout << msg << std::endl; }

int main()
{
  init_sdl();
  init_window_and_renderer();
  init_ttf();
  // init_audio();
  // setup_window_icon();
  // setup_texture();

  inputBox1 = new InputBox{24,
                           "../resources/font.ttf",
                           250,
                           20,
                           20,
                           SDL_Color{0, 0, 255, 255},
                           SDL_Color{255, 255, 255, 255}};
  inputBox2 = new InputBox{24,
                           "../resources/font.ttf",
                           250,
                           300,
                           20,
                           SDL_Color{0, 255, 0, 255},
                           SDL_Color{255, 255, 255, 255}};
  inputBox3 = new InputBox{24,
                           "../resources/font.ttf",
                           250,
                           580,
                           20,
                           SDL_Color{255, 0, 0, 255},
                           SDL_Color{255, 255, 255, 255},
                           &log};

  inputBox1->Initialize();
  inputBox2->Initialize();
  inputBox3->Initialize();

  // play_audio();
  // if (Mix_PlayingMusic())
  // {
  //   Mix_HaltMusic();
  // }

  main_loop();

  // Mix_FreeMusic(_music);
  // Mix_CloseAudio();
  inputBox1->Finalize();
  inputBox2->Finalize();
  inputBox3->Finalize();
  TTF_Quit();
  SDL_DestroyWindow(_window);
  SDL_Quit();
  exit(0);
}

// void init_audio()
// {
//   if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != 0)
//   {
//     printf("[Error] Error Initialising Audio : %s\n", SDL_GetError());
//   }
//   else
//   {
//     printf("Audio Initialised\n");
//   }
// }

// void setup_texture()
// {
//   _image = NULL;

//   // Load image at specified path
//   SDL_Surface* loadedSurface = IMG_Load("resources/floor.png");
//   if (loadedSurface == NULL)
//   {
//     printf("[Error] Unable to load image : %s\n", SDL_GetError());
//     exit(0);
//   }
//   else
//   {
//     _image = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
//     if (_image == NULL)
//     {
//       printf("[Error] Unable to create texture : %s\n", SDL_GetError());
//     }

//     SDL_FreeSurface(loadedSurface);
//   }
// }

// void setup_window_icon()
// {
//   SDL_Surface* iconSurface;
//   iconSurface = IMG_Load("resources/appicon.jpg");

//   // The icon requires the window pointer NOT the renderer
//   SDL_SetWindowIcon(_window, iconSurface);

//   // ...and can now free the appicon surface
//   SDL_FreeSurface(iconSurface);
// }

// void play_audio()
// {
//   _music = Mix_LoadMUS("resources/sound.ogg");
//   if (Mix_PlayMusic(_music, -1) != 0)
//   {
//     printf("[Error] Could not play music : %s", Mix_GetError());
//   }
// }