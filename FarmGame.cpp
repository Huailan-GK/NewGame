#include"FarmGame.h"
#include<iostream>

//构造函数
FarmGame::FarmGame():
    window(nullptr),renderer(nullptr),is_running(0)
{
    InitializeLands();
}

void FarmGame::InitializeLands()
{
    //三行三列土地
    for(int i=0;i<3;++i)
        for(int j=0;j<3;++j)
        lands.emplace_back(Position(100+i*(LAND_SIZE+30),
                                    200+j*(LAND_SIZE+30)));
    
    //解锁第一块土地
    lands[0].SetLocked(0);
}

//初始化SDL和游戏资源
bool FarmGame::Init()
{
    //初始化SDL
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        std::cerr<<"SDL初始化失败！错误："<<SDL_GetError()<<std::endl;
        return 0;
    }

    //创建窗口
    window=SDL_CreateWindow
    (
        "农场游戏 - 土地系统",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if(!window)
    {
        std::cerr<<"窗口创建失败！错误："<<SDL_GetError()<<std::endl;
        return 0;
    }

    //创建渲染器
    renderer=SDL_CreateRenderer
    (
        window,
        -1,
        SDL_RendererFlags::SDL_RENDERER_ACCELERATED|
        SDL_RendererFlags::SDL_RENDERER_PRESENTVSYNC
    );
    if(!renderer)
    {
        std::cerr<<"渲染器创建失败！错误："<<SDL_GetError()<<std::endl;
        return 0;
    }

    is_running=1;
    return 1;
}

//处理用户输入
void FarmGame::HandleInput()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        //窗口关闭
        if(event.type==SDL_QUIT)    is_running=0;
        else if (event.type==SDL_MOUSEBUTTONDOWN)
            HandleMouseClick(event.button.x,event.button.y);
    }
}

//处理鼠标点击
void FarmGame::HandleMouseClick(int x,int y)
{
    for(auto& land:lands)
    {
        Position pos=land.GetPosition();

        //矩形碰撞检测
        if(x>=pos.x&&x<=pos.x+LAND_SIZE&&
            y>=pos.y&&y<=pos.y+LAND_SIZE)
        {
            if(land.IsLocked())
            {
                std::cout<<"这块土地已锁定，无法种植！"<<std::endl;
            }
            else
            {
                std::cout<<"这块土地已解锁，可以种植！"<<std::endl;
            }
            break;
        }
    }
}

//渲染画面
void FarmGame::Render()
{
    SDL_SetRenderDrawColor(renderer,240,240,240,255);
    SDL_RenderClear(renderer);

    //绘制土地
    for(auto& land:lands)
    {
        Position pos=land.GetPosition();

        //创建矩形
        SDL_Rect land_rect=
        {
            pos.x,
            pos.y,
            LAND_SIZE,
            LAND_SIZE
        };
        if(land.IsLocked())
        {
            SDL_SetRenderDrawColor(renderer,150,150,150,255);//灰色
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 100, 200, 100, 255);//绿色
        }

        //绘制土地
        SDL_RenderFillRect(renderer,&land_rect);

        //绘制土地边框
        SDL_SetRenderDrawColor(renderer,50,150,50,255);//深绿色
        SDL_RenderDrawRect(renderer,&land_rect);
    }

    //更新屏幕显示
    SDL_RenderPresent(renderer);
}

//游戏主循环
void FarmGame::Run()
{
    if(!Init()) return;

    //主循环
    while(is_running)
    {
        HandleInput();
        Render();
        SDL_Delay(16);  //控制帧率（60FPS）
    }

    CleanUp();
}

//清理资源
void FarmGame::CleanUp()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}