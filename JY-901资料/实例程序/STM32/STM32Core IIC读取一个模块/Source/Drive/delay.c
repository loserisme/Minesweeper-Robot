/* delay.c file
��д�ߣ�Kevin
��ַ��http://RobotControl.taobao.com
����E-mail��1609370741@qq.com
���뻷����MDK-Lite  Version: 5.17
����ʱ��: 2013-11-30
���ԣ� ���������ڡ������ǿء���STM32Coreƽ̨����ɲ���
���ܣ�
�ṩ��ȷ����ʱAPI  ��΢�뼶 �ͺ��뼶��ʱ
------------------------------------
 */
#include "delay.h"
#include "misc.h"	 
static u8  fac_us=0;//us��ʱ������
static u16 fac_ms=0;//ms��ʱ������

//��ʼ���ӳٺ���
//SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
//SYSCLK:ϵͳʱ��
/**************************ʵ�ֺ���********************************************
*����ԭ��:		void SysTick_init(u8 SYSCLK,u16 nms)
*��������:		��ʼ���ӳ�ϵͳ��ʹ��ʱ����������״̬
*******************************************************************************/
void SysTick_init(u8 SYSCLK,u16 nms)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	SysTick->VAL =0x00;           //��ռ�����
	SysTick->LOAD = nms*SYSCLK*125;//72MHz,���1864ms
	SysTick->CTRL=3;//bit2���,ѡ���ⲿʱ��  HCLK/8
	fac_us=SYSCLK/8;		    
	fac_ms=(u16)fac_us*1000;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  NVIC_InitStructure.NVIC_IRQChannel = SysTick_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
unsigned char ucTimeFlag=0,ucDelayFlag=0;
void SysTick_Handler(void) 
{      
	ucTimeFlag=1;	if (ucDelayFlag) ucDelayFlag--;
}			
unsigned char CheckSystemTick(void)
{	
	if (ucTimeFlag) 
	{
		ucTimeFlag = 0;
		return(1);
	}
	else 
		return(0);
}				    
//��ʱnms
//ע��nms�ķ�Χ
//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK��λΪHz,nms��λΪms
/**************************ʵ�ֺ���********************************************
*����ԭ��:		void delay_ms(u16 nms)
*��������:		���뼶��ʱ  ��ʱnms  nms<=1864 
*******************************************************************************/

void delay_ms(u16 nms)
{	 		  	  
  u32 Start = 	SysTick->VAL;
	u32 Span =(u32)nms*fac_ms;//ʱ�����(SysTick->LOADΪ24bit)
	u32 End = 0;
		ucDelayFlag=Span/SysTick->LOAD;
		End = Span%SysTick->LOAD;
	if (Start>End)
	{
			End = Start-End;
		  while(ucDelayFlag);
			if (End<10)
				while(SysTick->VAL>10);
			else			
				while(SysTick->VAL>End); 
	}
	else
	{
			ucDelayFlag++;
			End = (Start+SysTick->LOAD)-End;
		  while(ucDelayFlag);			
			if (End<10)
				while(SysTick->VAL>10);
			else			
				while(SysTick->VAL>End); 
	}		  	    
}   

//��ʱnus
//nusΪҪ��ʱ��us��.
/**************************ʵ�ֺ���********************************************
*����ԭ��:		void delay_us(u32 nus)
*��������:		΢�뼶��ʱ  ��ʱnus  nms<=1864 
*******************************************************************************/		    								   
void delay_us(u32 nus)
{		
	u32 Start = 	SysTick->VAL;
	u32 Span =(u32)nus*fac_us;//ʱ�����(SysTick->LOADΪ24bit)
	u32 End = 0;
		ucDelayFlag=Span/SysTick->LOAD;
		End = Span%SysTick->LOAD;
	if (Start>End)
	{
			End = Start-End;
		  while(ucDelayFlag);
			if (End<10)
				while(SysTick->VAL>10);
			else			
				while(SysTick->VAL>End); 
	}
	else
	{
			ucDelayFlag++;
			End = (Start+SysTick->LOAD)-End;
		  while(ucDelayFlag);			
			if (End<10)
				while(SysTick->VAL>10);
			else			
				while(SysTick->VAL>End); 
	}		  	    
}

//------------------End of File----------------------------
