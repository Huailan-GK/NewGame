#include"Land.h"

//构造函数
Land::Land(Position p):
    pos(p),is_locked(1),has_crop(0){}

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