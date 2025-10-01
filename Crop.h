#ifndef CROP_H
#define CROP_H

#include<string>
#include<ctime>
#include<SDL2/SDL.h>

class Crop
{
protected:
    std::string name;   //作物名称
    int grow_time;      //生长时间（秒）
    time_t plant_time;  //种植时间戳
    bool is_ripe;       //是否成熟
    bool is_quality;    //是否为高品质作物
    int value;          //价值（金币）

public:

    //构造函数：设定名字，生长时间，植物价值
    Crop(const std::string s,int gt,int v)
    :name(s),grow_time(gt),is_ripe(0),is_quality(0),value(v)
    {
        plant_time=time(nullptr);
    }

    //虚析构函数
    virtual ~Crop() = default;

    //更新生长状态
    virtual void UpdateGrowth()
    {
        if(!is_ripe)
        {
            time_t current_time=time(nullptr);
            double elapsed=difftime(current_time,plant_time);
            is_ripe=(elapsed>=grow_time);
        }
    }

    //收获处理
    virtual void Harvest()
    {
        if(is_ripe)
            is_quality=(rand()%100)<30; //30%概率高品质
    }

    //获取剩余生长时间
    int GetRemainingTime() const
    {
        if(is_ripe) return 0;
        time_t current_time=time(nullptr);
        int remaining=grow_time-static_cast<int>(difftime(current_time,plant_time));
        return (remaining>0)? remaining:0;
    }

    //获得名字
    std::string GetName() const{return name;};
    //获得成熟情况
    bool GetRipe() const {return is_ripe;}
    //获得质量情况
    bool GetQuality() const {return is_quality;}
    
    //获取价值
    int GetValue() const
    {
        return is_quality? value*2:value;
    }

    //获取颜色
    virtual SDL_Color GetColor() const =0;
};

class Wheat:public Crop
{
public:
    //小麦，20秒成熟，10金币
    Wheat():Crop("小麦",20,10){}

    SDL_Color GetColor() const override
    {
        return GetRipe()? 
            SDL_Color{255,215,0,255}:   //成熟：金色
            SDL_Color{150,255,150,255}; //未成熟：浅绿色

    }
};

class Carrat:public Crop
{
public:
    //胡萝卜，25秒成熟，15金币
    Carrat():Crop("胡萝卜",20,15){}

    SDL_Color GetColor() const override
    {
        return GetRipe()? 
            SDL_Color{255,165,0,255}:   //成熟：橙色
            SDL_Color{255,218,185,255}; //未成熟：浅橙色

    }
};

class Potato:public Crop
{
public:
    //土豆，30秒成熟，20金币
    Potato():Crop("土豆",30,20){}

    SDL_Color GetColor() const override
    {
        return GetRipe()? 
            SDL_Color{139,69,19,255}:   //成熟：棕色
            SDL_Color{210,180,140,255}; //未成熟：浅棕色

    }
};
#endif