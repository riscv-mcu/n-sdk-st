#include "adc.h"
//#include "delay.h"					   
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEKս��STM32������V3
//ADC ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2015/1/14
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
	   
//��ʼ��ADC1
//�������ǽ��Թ���ͨ��Ϊ��
//����Ĭ�Ͻ�����ͨ��1																	   
void  Adc1_Init(void)
{    
	//�ȳ�ʼ��IO��
 	RCC->APB2ENR|=1<<2;    //ʹ��PORTA��ʱ�� 
	RCC->APB2ENR|=1<<3;
	RCC->APB2ENR|=1<<4;
	GPIOA->CRL&=0X00000000;//PA0~7 anolog���� 
	//GPIOB->CRL&=0XFFFFFF00;//PB0~1
	GPIOC->CRL&=0XFF000000;//PC0~5
	RCC->APB2ENR|=1<<9;    //ADC1ʱ��ʹ��	  
	RCC->APB2RSTR|=1<<9;   //ADC1��λ
	RCC->APB2RSTR&=~(1<<9);//��λ����	    
	RCC->CFGR&=~(3<<14);   //��Ƶ��������	
	//SYSCLK/DIV2=12M ADCʱ������Ϊ12M,ADC���ʱ�Ӳ��ܳ���14M!
	//���򽫵���ADC׼ȷ���½�! 
	RCC->CFGR|=2<<14;      	 
	ADC1->CR1&=0XF0FFFF;   //����ģʽ����
	ADC1->CR1|=0<<16;      //��������ģʽ  
	ADC1->CR1&=~(1<<8);    //��ɨ��ģʽ	  
	ADC1->CR2&=~(1<<1);    //����ת��ģʽ
	ADC1->CR2&=~(7<<17);	   
	ADC1->CR2|=7<<17;	   //��������ת��  
	
	ADC1->CR2|=1<<22;			//SWSTART
	
	ADC1->CR2|=1<<20;      //ʹ�����ⲿ����(SWSTART)!!!	����ʹ��һ���¼�������
	ADC1->CR2&=~(1<<11);   //�Ҷ���	 
	ADC1->SQR1&=~(0XF<<20);
	ADC1->SQR1|=0<<20;     //1��ת���ڹ��������� Ҳ����ֻת����������1 			   
	//����ͨ��1�Ĳ���ʱ��
	ADC1->SMPR2&=~(3*1);   //ͨ��1����ʱ�����	  
 	ADC1->SMPR2|=7<<(3*1); //ͨ��1  239.5����,��߲���ʱ�������߾�ȷ��	 
	ADC1->CR2|=1<<0;	   //����ADת����	 
//	ADC1->CR2|=1<<3;       //ʹ�ܸ�λУ׼  
//	while(ADC1->CR2&1<<3); //�ȴ�У׼���� 			 
    //��λ���������ò���Ӳ���������У׼�Ĵ�������ʼ�����λ��������� 		 
//	ADC1->CR2|=1<<2;        //����ADУ׼	   
//	while(ADC1->CR2&1<<2);  //�ȴ�У׼����
	//��λ�����������Կ�ʼУ׼������У׼����ʱ��Ӳ�����  
}				  
//���ADC1ĳ��ͨ����ֵ
//ch:ͨ��ֵ 0~16
//����ֵ:ת�����
u16 Get_Adc(u8 ch)   
{
	//����ת������	  		 
	ADC1->SQR3&=0XFFFFFFE0;//��������1 ͨ��ch
	ADC1->SQR3|=ch;		  			    
	ADC1->CR2|=1<<22;       //��������ת��ͨ�� 
	while(!(ADC1->SR&1<<1));//�ȴ�ת������	 	   
	return ADC1->DR;		//����adcֵ	
}
//��ȡͨ��ch��ת��ֵ��ȡtimes��,Ȼ��ƽ�� 
//ch:ͨ�����
//times:��ȡ����
//����ֵ:ͨ��ch��times��ת�����ƽ��ֵ
u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
} 
	 









