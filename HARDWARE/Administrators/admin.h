#ifndef _ADMIN_H_
#define _ADMIN_H_

#include <sys.h>

//#define FLASH_SAVE_ADDR_2 0x08080000
//#define SIZE_2 sizeof(int_to_char)


extern u8 number_1[30];
extern u8 number_2[30];
//struct duty_student
//{
//	u8 Monday[20];
//	u8 Tuesday[20];
//	u8 Wednesday[20];
//	u8 Thursday[20];
//	u8 Friday[20];
//	u8 Saturday[20];
//}stu1;


extern u8 s_1;
extern u8 cun[10];
extern u8 depart_flag;
extern u8 data_flag;


u8 data_choose(void);
u8 depart_choose(void);
u8 timeset_input(void);
u8 password_input(void);
void Local_time_set(void);
void worktime_set(void);
void finworktime_set(void);
//void password_set(void);
void zhuanhua(u8 flag);
void File_xianshi(void);
void write_to_file(void );
void show_duty_student(void);



#endif



