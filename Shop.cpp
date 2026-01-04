#include"Shop.h"
#include<sstream>

//初始化商品列表
void Shop::InitShopItems()
{
    shop_items.clear(); 
    shop_items.push_back({"小麦种子", 1, 8});
    shop_items.push_back({"胡萝卜种子", 2, 12});
    shop_items.push_back({"土豆种子", 3, 18});
}

//切换商品开关
void Shop::ToggleShop()
{
    is_shop_open=!is_shop_open;
}

//渲染商店界面
void Shop::RenderShop()
{
    if(!is_shop_open||!renderer)    return ;

    //保留混合模式
    SDL_BlendMode old_blend_mode;
    SDL_GetRenderDrawBlendMode(renderer,&old_blend_mode);
    //设置混合模式
    SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);

    //计算商店坐标
    int shop_x=(SCREEN_WIDTH-SHOP_WIDTH)/2;
    int shop_y=(SCREEN_HEIGHT-SHOP_HEIGHT)/2;

    //绘制商店背景
    SDL_SetRenderDrawColor(renderer,50,50,50,150);  //半透明深灰色
    SDL_Rect shop_rect={shop_x,shop_y,SHOP_WIDTH,SHOP_HEIGHT};
    SDL_RenderFillRect(renderer,&shop_rect);
    //绘制商店标题
    SDL_Color title_color={255,215,0,255};
    RenderText("农场商店",shop_x+SHOP_WIDTH/2-40,shop_y+10,title_color);

    int item_start_y=shop_y+50;
    int item_line_height=60;
    SDL_Color item_color={255,255,255,255};
    SDL_Color price_color={0,255,0,255};
    
    //商店物品渲染
    int i=0;
    for(auto item:shop_items)
    {
        int current_y=item_start_y+i++*item_line_height;

        std::string item_text = std::to_string(i) + ". " + item.name;
        RenderText(item_text, shop_x + 20, current_y, item_color);

        std::string price_text = "价格：" + std::to_string(item.price) + " 金币";
        RenderText(price_text, shop_x + 200, current_y, price_color);
    }

    SDL_Color tip_color = {180, 180, 180, 255};
    RenderText("按S键关闭商店", shop_x + SHOP_WIDTH/2 - 60, shop_y + SHOP_HEIGHT - 30, tip_color);
    //恢复原有混合模式
    SDL_SetRenderDrawBlendMode(renderer, old_blend_mode);
}

//渲染文字
void Shop::RenderText(const std::string& text,int x,int y,SDL_Color color)
{
    if (!font || !renderer) return;

    // 转换文字为SDL表面
    SDL_Surface* text_surface = TTF_RenderUTF8_Solid(font, text.c_str(), color);
    if (!text_surface) return;

    // 转换表面为纹理
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    if (!text_texture) {
        SDL_FreeSurface(text_surface);
        return;
    }

    // 绘制纹理
    SDL_Rect text_rect = {x, y, text_surface->w, text_surface->h};
    SDL_RenderCopy(renderer, text_texture, nullptr, &text_rect);

    // 释放资源（避免内存泄漏）
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
}