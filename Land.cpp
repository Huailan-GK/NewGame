#include"Land.h"

//构造函数
Land::Land(Position p):
    pos(p),is_locked(1),crop(0){}

//获取土地位置
Position Land::GetPosition()
{
    return pos;
}

//检查土地是否被锁定
bool Land::IsLocked()
{
    return is_locked;
}

//锁定/解锁土地
void Land::SetLocked(bool locked)
{
    is_locked=locked;
}

//种植作物
bool Land::PlantCrop(Crop* new_crop)
{
    if(!is_locked&&!crop)
    {
        crop=new_crop;
        return 1;
    }
    return 0;
}

//更新作物生长
void Land::UpdateCropGrowth()
{
    if(crop)
        crop->UpdateGrowth();
}