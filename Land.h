#ifndef LAND_H
#define LAND_H
#include"Position.h"
#include"Crop.h"
class Land
{
private:
    Position pos;//土地位置
    bool is_locked;
    Crop* crop;
public:
    //构造函数，初始化土地信息
    Land(Position p);
    //获取土地位置
    Position GetPosition();
    //是否被锁定
    bool IsLocked();
    //锁定/解锁土地
    void SetLocked(bool locked);
    
    //种植作物
    bool PlantCrop(Crop* new_crop);

    //获取作物
    Crop* GetCrop() const {return crop;};

    //更新作物生长
    void UpdateCropGrowth();
};
#endif