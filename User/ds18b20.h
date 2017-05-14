#ifndef __DS18B20_H
#define __DS18B20_H 
 
#include <stm32f10x.h>
#include "GPIOLIKE51.h"
#include "stm32f10x_gpio.h"

#define DS18B20_GPIO GPIOB
#define DS18B20_PIN  5

//IO方向设置
#define DS18B20_IO_IN()  {GPIOB->CRL&=0XFFFFFFF0;GPIOB->CRL|=8<<DS18B20_PIN;}
#define DS18B20_IO_OUT() {GPIOB->CRL&=0XFFFFFFF0;GPIOB->CRL|=3<<DS18B20_PIN;}
////IO操作函数											   
#define	DS18B20_DQ_OUT PBout(DS18B20_PIN) //数据端口	PB5
#define	DS18B20_DQ_IN  PBin(DS18B20_PIN)  //数据端口	PB5 
   	
u8 DS18B20_Init(void);			//初始化DS18B20
short DS18B20_Get_Temp(void);	//获取温度
void DS18B20_Start(void);		//开始温度转换
void DS18B20_Write_Byte(u8 dat);//写入一个字节
u8 DS18B20_Read_Byte(void);		//读出一个字节
u8 DS18B20_Read_Bit(void);		//读出一个位
u8 DS18B20_Check(void);			//检测是否存在DS18B20
void DS18B20_Rst(void);			//复位DS18B20    
#endif















