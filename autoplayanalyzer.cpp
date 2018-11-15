#include "autoplayanalyzer.h"

AutoPlayAnalyzer::AutoPlayAnalyzer()
{

}

bool AutoPlayAnalyzer::canJump(GameData data)
{
    // 下面是示例，要删掉，可以在游戏中按A键打开AutoPlay效果，此时canJump函数会生效，当canJump返回true时就会跳跃，按S键可以关闭AutoPlay，此时canJump无效
    if(data.bird.y > 200)
        return true;
    return false;
}
