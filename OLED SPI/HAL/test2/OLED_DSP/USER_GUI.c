
#include "USER_GUI.h"
#include "string.h"

void Disp_Title(void) {
  //------�ػ�������ʾ����---------------------
  //OLED_Clear;
  Show_Str(0, 0, "������Gizwits", 16, 0);
  Show_Str(0, 2, "����Ӳ����������", 16, 0);
  Show_Str(0, 4, "���Ʒ���ƽ̨", 16, 0); 
  Show_Str(0, 6, "����������������", 16, 0); 
}
