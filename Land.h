#ifndef LAND_H
#define LAND_H
#include"Position.h"
class Land
{
private:
    Position pos;//土地位置
    bool is_locked;
    bool has_crop;
public:
    //构造函数，初始化土地信息
    Land(Position p);
    //获取土地位置
    Position GetPosition();
    //是否被锁定
    bool IsLocked();
    //锁定/解锁土地
    void SetLocked(bool locked);
};
#endif