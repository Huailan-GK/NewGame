#ifndef SHOP_H
#define SHOP_H

#include<vector>
#include<string>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>


struct ShopItem
{
    std::string name;
    int crop_type;
    int price;
};

class Shop
{
private:

    std::vector<ShopItem> shop_items;   //商品列表
    bool is_shop_open;  //商店是否打开
    SDL_Renderer* renderer;
    TTF_Font* font;

    const int SHOP_WIDTH=400;
    const int SHOP_HEIGHT=300;
    const int SCREEN_WIDTH=800; //窗口宽度
    const int SCREEN_HEIGHT=600; //窗口高度

public:

    Shop(SDL_Renderer* renderer,TTF_Font* ttf):
    renderer(renderer),font(ttf),is_shop_open(0)
    {   
        InitShopItems();
    }
    ~Shop()=default;

    //初始化商品列表
    void InitShopItems();
    //渲染商店界面
    void RenderShop();
    //切换商店开关状态
    void ToggleShop();
    //购买商品
    ShopItem* Purchase(int x,int y);
    //获取状态
    bool IsOpen() const
    {
        return is_shop_open;
    }
    //渲染文字的函数
    void RenderText(const std::string& text,int x,int y,SDL_Color color);
};

#endif