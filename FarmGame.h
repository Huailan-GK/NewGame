#ifndef FARM_GAME_H
#define FARM_GAME_H
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<vector>
#include"Land.h"

class FarmGame
{
private:
    SDL_Window* window; //窗口
    SDL_Renderer* renderer;  //SDL渲染器
    bool is_running;    //是否运行

    TTF_Font* font; //字体对象
    std::string message;    //提示信息
    Uint32 message_time;    //时间戳
    
    const int SCREEN_WIDTH=800; //窗口宽度
    const int SCREEN_HEIGHT=600; //窗口高度
    const int LAND_SIZE=80;     //土地大小

    std::vector<Land> lands;    //土地群

public:
    //构造函数
    FarmGame();
    //析构函数
    ~FarmGame();

    //初始化SDL和游戏资源
    bool Init();

    //游戏主循环
    void Run();

private:
    //初始化土地
    void InitializeLands();

    //处理用户输入
    void HandleInput();

    //处理鼠标点击
    void HandleMouseClick(int x,int y);

    //游戏画面渲染
    void Render();

    //清理资源
    void CleanUp();

    //更新提示信息状态
    void Update();

    //渲染文字的函数
    void RenderText(const std::string& text,int x,int y,SDL_Color color);
};
#endif