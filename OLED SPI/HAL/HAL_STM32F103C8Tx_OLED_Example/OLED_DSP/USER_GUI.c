
#include "USER_GUI.h"
#include "string.h"

void Disp_Title(void) {
  //------重绘数据显示界面---------------------
  //OLED_Clear;
  Show_Str(0, 0, "机智云Gizwits", 16, 0);
  Show_Str(0, 2, "智能硬件自助开发", 16, 0);
  Show_Str(0, 4, "及云服务平台", 16, 0); 
  Show_Str(0, 6, "物联网开发者社区", 16, 0); 
}
