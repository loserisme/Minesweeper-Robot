/*
编写者：Kevin
网址：http://RobotControl.taobao.com
作者E-mail：1609370741@qq.com
编译环境：MDK-Lite  Version: 5.17
初版时间: 2016-1-31
测试： 本程序已在【君悦智控】的STM32Core平台上完成测试
功能：
用STM32Core平台IIC接口读取JY901的数据，然后通过串口1打印到串口助手。
接线
USB-TTL工具                 STM32Core              JY901
VCC          -----           VCC        ----        VCC
TX           -----           RX1     
RX           -----           TX1
GND          -----           GND        ----        GND
                             SDA2       ----        SDA
							 SCL2       ----        SCL
------------------------------------
 */
#include <string.h>
#include <stdio.h>
#include "Main.h"
#include "REG.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "UART1.h"
#include "delay.h"
#include "IOI2C.h"
#include "hw_config.h"

unsigned char chrTemp[30];
unsigned char str[100];
float a[3],w[3],h[3],Angle[3];
	
void ShortToChar(short sData,unsigned char cData[])
{
	cData[0]=sData&0xff;
	cData[1]=sData>>8;
}
short CharToShort(unsigned char cData[])
{
	return ((short)cData[1]<<8)|cData[0];
}
void ReadData(void)
{
	IICreadBytes(0x50, AX, 24,&chrTemp[0]);
		a[0] = (float)CharToShort(&chrTemp[0])/32768*16;
		a[1] = (float)CharToShort(&chrTemp[2])/32768*16;
		a[2] = (float)CharToShort(&chrTemp[4])/32768*16;
		w[0] = (float)CharToShort(&chrTemp[6])/32768*2000;
		w[1] = (float)CharToShort(&chrTemp[8])/32768*2000;
		w[2] = (float)CharToShort(&chrTemp[10])/32768*2000;
		h[0] = CharToShort(&chrTemp[12]);
		h[1] = CharToShort(&chrTemp[14]);
		h[2] = CharToShort(&chrTemp[16]);
		Angle[0] = (float)CharToShort(&chrTemp[18])/32768*180;
		Angle[1] = (float)CharToShort(&chrTemp[20])/32768*180;
		Angle[2] = (float)CharToShort(&chrTemp[22])/32768*180;
		
		sprintf((char*)str,"0x50:  a:%.3f %.3f %.3f w:%.3f %.3f %.3f  h:%.0f %.0f %.0f  Angle:%.3f %.3f %.3f \r\n",a[0],a[1],a[2],w[0],w[1],w[2],h[0],h[1],h[2],Angle[0],Angle[1],Angle[2]);
		UART1_Put_String(str);		
		USB_TxWrite(str, strlen((char*)str));
}

int main(void)
{  
		
	USB_Config();		
	SysTick_init(72,10);
	Initial_UART1(115200);
	IIC_Init();
	
	while (1)
	{
		delay_ms(100);
		ReadData();
	
	
    }
}



