#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "app_sdl2.h"

// 画实心圆函数（通用）
void DrawFilledCircle(SDL_Renderer *renderer, int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);

    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, cx + dx, cy + dy);
            }
        }
    }
}

// 渲染文字到屏幕居中
void DrawTextCenter(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, SDL_Color color)
{
    // 生成文字表面
    SDL_Surface *surface = TTF_RenderUTF8_Solid(font, text, color);
    if (!surface)
        return;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect;
    rect.w = surface->w;
    rect.h = surface->h;
    rect.x = x - rect.w / 2;
    rect.y = y - rect.h / 2;

    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

int32_t app_sdl2_run(void)
{

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init(); // 初始化字体

    SDL_Window *window = SDL_CreateWindow(
        "圆上显示文字",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // 加载中文字体 换成你实际的字体路径
    TTF_Font *font = TTF_OpenFont("/home/mike/hive/util_font/Simhei.ttf", 36);
    if (!font)
    {
        printf("字体加载失败\n");
        return -1;
    }

    SDL_Color textColor = {255, 255, 255, 255}; // 白色文字

    int running = 1;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = 0;
        }

        // 清屏黑色
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // 画红色实心圆
        DrawFilledCircle(renderer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 120, 255, 0, 0);

        // 在圆正中间画：on 开
        DrawTextCenter(renderer, font, "on 开", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, textColor);

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
