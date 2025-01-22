#include "sys.h"
#include "delay.h"
#include "BEEP.h"
#include "DS1302.h"
#include "oled.h"
#include "stdio.h"
#include "LCD1602v1.h"
#include "MatrixKey.h"
#include "DHT11.h"
#include "OLED_R.h"
/*
by-BilibiliԵ������
*/
DHT11_Data_TypeDef DHT11_Data;
uchar time_data[6]={0};//��ȡDS1302��ǰʱ�仺�����
uchar bell_data[3]={0};//�������ý���
uchar jishi_data[3]={0};      //��ʱ
uchar daojishi_data[3]={0};    //����ʱ
uchar reverse_bell_data[3]={0};  //���������
uchar bell_flag=0;//���幦�ܿ���
uchar bell_onoff=0;//���忪��

void display_year(uchar a,uchar flag)//flagΪ1 ʱ����ʾ���ݣ�0ʱ��Ӧ�����Ļ
{
	if(flag)
	{
	OLED_ShowChar(24, 0, a/10+'0');//��	
	OLED_ShowChar(32, 0, a%10+'0');
	}
	else
	{
	//�����λ
	OLED_ClearChar(24, 0);
	}	
}
void display_month(uchar a,uchar flag)
{
	if(flag)
	{
	OLED_ShowChar(56, 0, a/10+'0');//��
	OLED_ShowChar(64, 0, a%10+'0');
	}
	else
	{
	//�����λ
	OLED_ClearChar(56, 0);
	}
}
void display_day(uchar a,uchar flag)
{
	if(flag)
	{
	OLED_ShowChar(88, 0, a/10+'0');//��
	OLED_ShowChar(96, 0, a%10+'0');
	}
	else
	{
	//�����λ
	OLED_ClearChar(88, 0);
	}
}
void display_hour(uchar a,uchar flag)
{
	if(flag)
	{
	OLED_ShowChar24(16, 3, a/10+'0');//ʱ
	OLED_ShowChar24(28, 3, a%10+'0');
	}
	else
	{
	//���ʱλ
	OLED_ClearChar24(16, 3);
	}
}
void display_min(uchar a,uchar flag)
{
	if(flag)
	{
	OLED_ShowChar24(52, 3, a/10+'0');//��
	OLED_ShowChar24(64, 3, a%10+'0');
	}
	else
	{
	//�����λ
	OLED_ClearChar24(52, 3);
	}
}
void display_sec(uchar a,uchar flag)
{
	if(flag)
	{
	OLED_ShowChar24(88, 3, a/10+'0');//��
	OLED_ShowChar24(100, 3, a%10+'0');
	}
	else
	{
	//�����λ
	OLED_ClearChar24(88, 3);
	}
}

void display(uchar a,uchar flag,uchar shift)
{
	switch(shift)
	{
	case 0:	display_sec(a,flag); break;
	case 1:	display_min(a,flag);  break;
	case 2:	display_hour(a,flag);  break;
	case 3:	display_day(a,flag);  break;
	case 4:	display_month(a,flag);  break;
	case 5:	display_year(a,flag); break;
	default : break;
	}

}


void show_time(uchar show_data[6])//ʱ���ӡ����
{

	OLED_ShowChar(24, 0, show_data[0]/10+'0');//��	
	OLED_ShowChar(32, 0, show_data[0]%10+'0');
	
	OLED_ShowChar(56, 0, show_data[1]/10+'0');//��
	OLED_ShowChar(64, 0, show_data[1]%10+'0');
	
	OLED_ShowChar(88, 0, show_data[2]/10+'0');//��
	OLED_ShowChar(96, 0, show_data[2]%10+'0');
	
	OLED_ShowChar24(16, 3, show_data[3]/10+'0');//ʱ
	OLED_ShowChar24(28, 3, show_data[3]%10+'0');
		
	OLED_ShowChar24(40, 3, ':');
		
	OLED_ShowChar24(52, 3, show_data[4]/10+'0');//��
	OLED_ShowChar24(64, 3, show_data[4]%10+'0');
				
	OLED_ShowChar24(76, 3, ':');
		
	OLED_ShowChar24(88, 3, show_data[5]/10+'0');//��
	OLED_ShowChar24(100, 3, show_data[5]%10+'0');	
}

void show_time1(uchar show_data[3])//ʱ���ӡ����(��ʱ����)
{

	
	
	OLED_ShowChar24(16, 3, show_data[0]/10+'0');//ʱ
	OLED_ShowChar24(28, 3, show_data[0]%10+'0');
		
	OLED_ShowChar24(40, 3, ':');
		
	OLED_ShowChar24(52, 3, show_data[1]/10+'0');//��
	OLED_ShowChar24(64, 3, show_data[1]%10+'0');
				
	OLED_ShowChar24(76, 3, ':');
		
	OLED_ShowChar24(88, 3, show_data[2]/10+'0');//��
	OLED_ShowChar24(100, 3, show_data[2]%10+'0');	
}






int main(void)
{
	uchar set_run=0;//����run״̬��ʶ��
	uchar set_bell=0;//����bell״̬��ʶ��
  uchar set_jishi=0;  //��ʱģʽ
  uchar set_jishi_r=0;
  uchar set_jishi_rr=0;
  
  uchar now_hour=0;
  uchar now_min=0;
  uchar now_sec=0;   //��ʱʱ�ĵ�ʱʱ��
  int jishi_hour=0;
  int jishi_min=0;
  int jishi_sec=0;  //��ʱʵ��ʱ��
  
  uchar set_daojishi=0;   //����ʱģʽ
  uchar set_daojishi_r=0;
  uchar set_daojishi_rr=0;
  uchar all_hour=0;
  uchar all_min=0;
  uchar all_sec=0;   //����ʱʱ����ʱ��
  int daojishi_hour=0;
  int daojishi_min=0;
  int daojishi_sec=0; 
  
  
  uchar set_shift_daojishi=0;
  
  
  
  uchar set_reverse_bell=0;
  uchar set_reverse_bell_r=0;
  uchar all_reverse_hour=0;
  uchar all_reverse_min=0;
  uchar all_reverse_sec=0;   //����������ʱ����ʱ��
  int reverse_hour=0;
  int reverse_min=0;
  int reverse_sec=0; 
  
  
	uchar set_shift=0;//��ʱλ�ñ�ʶ��
	uchar set_shift_bell=0;//bell��ʱλ�ñ�ʶ��
	uchar init_time[6]={24,9,7,20,00,15};//��ʼ��ʱ�����
	
	delay_init();
	delay_ms(50);
	
	BEEP_GPIO_Init();
	MatrixKey_Init(); 			//������ʼ��
	OLED_Init();
  OLED_Init_r();
	DS1302_init(init_time);
  DHT11_GPIO_Config();
	
	OLED_Clear();
	OLED_ShowNum(8,0, 20, 2,0);
	OLED_ShowCH(40,0,"��");
	OLED_ShowCH(72,0,"��");	
	OLED_ShowCH(104,0,"��");
	
	BEEP=0;
	
  
  
	while(1)
	{
  OLED_ShowNum(8,0, 20, 2,0);
	OLED_ShowCH(40,0,"��");
	OLED_ShowCH(72,0,"��");	
	OLED_ShowCH(104,0,"��");
	
/*�����߼�*/
	switch(MatrixKey_GetValue())
	{
	case 1: //����run��
			set_run=1;
	//��ȡ��ǰʱ�䲢��ʾ
			DS1302_Readtime();
			show_time(time_data);
			while(set_run)
			{

				//��Ӧ����λ��˸
				display(time_data[5-set_shift],0,set_shift);
				delay_ms(50);
				display(time_data[5-set_shift],1,set_shift);

				switch(MatrixKey_GetValue())
				{
					case 1: DS1302_SetTime(time_data);set_run = 0; break;//�ڶ��ΰ���run������ʱ�䲢�˳�����
					case 2: if(set_shift++>4)set_shift=0;break;//��λ
					case 3: break;
					case 4: time_data[5-set_shift]++;break;//up
					case 5: time_data[5-set_shift]--;break;//down
					default : break;
				}
			}				break;
	case 2:	bell_onoff=0;BEEP=0; break;//�ر�����
	case 3: set_bell=1;//�����������ü�
	//��ȡ��ǰ�趨ʱ�䲢��ʾ
			display_hour(bell_data[0],1);
			display_min(bell_data[1],1);
			display_sec(bell_data[2],1);
			while(set_bell)
			{
				//��Ӧ����λ��˸
				display(bell_data[2-set_shift_bell],0,set_shift_bell);
				delay_ms(50);
				display(bell_data[2-set_shift_bell],1,set_shift_bell);

				switch(MatrixKey_GetValue())
				{
					case 1: bell_flag=!bell_flag;show_bell(bell_flag);	
									break;//������ر�����ʹ��
					case 2: if(set_shift_bell++>1)set_shift_bell=0;break;//�ƶ�����λ��
					case 3: set_bell=0;break;//�˳�ʱ������
					case 4: bell_data[2-set_shift_bell]++;break;//up
					case 5: bell_data[2-set_shift_bell]--;break;//down
					default : break;
				}
			}		break;
	case 4: break;
	case 5: break;
  case 6:     //���¼�ʱģ��
      set_jishi_r=1;
      while(set_jishi==0)
      {
        now_hour=time_data[3];
        now_min=time_data[4];
        now_sec=time_data[5];//��ȡ��ʱ��ʱ��
        set_jishi=1;
      }
      while(set_jishi_r==1)
      { 
        
        jishi_hour=time_data[3]-now_hour;
        jishi_min=time_data[4]-now_min;
        jishi_sec=time_data[5]-now_sec;
        if(jishi_sec<0)
        {
          jishi_min--;
          jishi_sec+=60;
        }
        if(jishi_min<0)
        {
          jishi_hour--;
          jishi_min+=60;
        }
        jishi_data[0]=jishi_hour;
        jishi_data[1]=jishi_min;
        jishi_data[2]=jishi_sec;
        DS1302_Readtime();
        show_time1(jishi_data);
        switch(MatrixKey_GetValue())
          {
            case 6: set_jishi_r=0;set_jishi=0; break;//�ռ�ʱ
            case 1: set_jishi_rr=1;
                    while(set_jishi_rr==1)
                    {
                      show_time1(jishi_data);
                      if(MatrixKey_GetValue()==2)
                      {
                        set_jishi_rr=0;
                        break;
                      }
                    }
                    break;
            
            default : break;
          }
      }  break ;
  case 7:
    set_daojishi=1;//���µ���ʱ���ü�
	//��ȡ��ǰ�趨ʱ�䲢��ʾ
			display_hour(daojishi_data[0],1);
			display_min(daojishi_data[1],1);
			display_sec(daojishi_data[2],1);
			while(set_daojishi)
			{
				//��Ӧ����λ��˸
				display(daojishi_data[2-set_shift_daojishi],0,set_shift_daojishi);
				delay_ms(50);
				display(daojishi_data[2-set_shift_daojishi],1,set_shift_daojishi);

				switch(MatrixKey_GetValue())
				{
					case 1: 
            set_daojishi_r=1;
            
            while(set_daojishi_rr==0)
            {
              DS1302_Readtime();
              all_hour=daojishi_data[0]+time_data[3];
              all_min=daojishi_data[1]+time_data[4];
              all_sec=daojishi_data[2]+time_data[5];//��ȡ��ʱ��ʱ��
              set_daojishi_rr=1;
            }
            while(set_daojishi_r==1)
            {
              daojishi_hour=all_hour-time_data[3];
              daojishi_min=all_min-time_data[4];
              daojishi_sec=all_sec-time_data[5];
               if(daojishi_sec<0)
              {
                daojishi_min--;
                daojishi_sec+=60;
              }
              if(daojishi_min<0)
              {
                daojishi_hour--;
                daojishi_min+=60;
              }
               if(daojishi_sec>=60)
              {
                daojishi_sec-=60;
                daojishi_min++; 
              }
              if(daojishi_min>=60)
              {
                daojishi_min-=60;
                daojishi_hour++; 
              }
              if(daojishi_hour>=24)
              {
                daojishi_hour-=24;
              }
             
              daojishi_data[0]=daojishi_hour;
              daojishi_data[1]=daojishi_min;
              daojishi_data[2]=daojishi_sec;
              DS1302_Readtime();
              show_time1(daojishi_data);
              if(MatrixKey_GetValue()==3)//����ʱ��һ��Ȳ����ˣ�����ʱ��
              {
                set_daojishi=0;
                set_daojishi_r=0;
                set_daojishi_rr=0;
              }
              while(daojishi_data[0]==0&&daojishi_data[1]==0&&daojishi_data[2]==0)
              {
                BEEP=!BEEP;
                delay_ms(1);
                
                if(MatrixKey_GetValue()==7)//����ʱ��������������ʱ��
                {
                  set_daojishi=0;
                  set_daojishi_r=0;
                  set_daojishi_rr=0;
                  BEEP=0;
                  break;
                }
              }
            }
			       		break;//������ر�����ʹ��
					case 2: if(set_shift_daojishi++>1)set_shift_daojishi=0;break;//�ƶ�����λ��
					case 3: set_daojishi=0;break;//�˳�ʱ������
					case 4: daojishi_data[2-set_shift_daojishi]++;break;//up
					case 5: daojishi_data[2-set_shift_daojishi]--;break;//down
					default : break;
				}
			}		break;
  case 8:
    set_reverse_bell=1;
    while(set_reverse_bell_r==0)
    {
     DS1302_Readtime();
     all_reverse_hour=time_data[3]*2;
     all_reverse_min=time_data[4]*2;
     all_reverse_sec=time_data[5]*2;//��ȡ��ʱ��ʱ��
     set_reverse_bell_r=1;
    }
    while(set_reverse_bell==1)
            {
              reverse_hour=all_reverse_hour-time_data[3];
              reverse_min=all_reverse_min-time_data[4];
              reverse_sec=all_reverse_sec-time_data[5];
               if(reverse_sec<0)
              {
                reverse_min--;
                reverse_sec+=60;
              }
              if(reverse_min<0)
              {
                reverse_hour--;
                reverse_min+=60;
              }
              if(reverse_hour<0)
              {
                reverse_hour+=24;
              }
               if(reverse_sec>=60)
              {
                reverse_sec-=60;
                reverse_min++; 
              }
              if(reverse_min>=60)
              {
                reverse_min-=60;
                reverse_hour++; 
              }
              if(reverse_hour>=24)
              {
                reverse_hour-=24;
              }
             
              reverse_bell_data[0]=reverse_hour;
              reverse_bell_data[1]=reverse_min;
              reverse_bell_data[2]=reverse_sec;
              DS1302_Readtime();
              show_time1(reverse_bell_data);
              if(MatrixKey_GetValue()==8)
              {
                set_reverse_bell_r=0;
                set_reverse_bell=0;
              }
            }
            
    break;
  case 9:
    while(1)
    {
      OLED_Clear_r();
      OLED_ShowString(1, 1, "temp:");
	    OLED_ShowString(2, 1, "humidity:");
      while(1)
      {
        if(Read_DHT11(&DHT11_Data) == SUCCESS)
        {
          OLED_ShowNum_r(2, 10, DHT11_Data.humi_int, 2);
          OLED_ShowString(2, 12, ".");
          OLED_ShowNum_r(2, 13, DHT11_Data.humi_deci, 2);
          
          OLED_ShowNum_r(1, 6, DHT11_Data.temp_int, 2);
          OLED_ShowString(1, 8, ".");
          OLED_ShowNum_r(1, 9, DHT11_Data.temp_deci, 1);
          
        }
        if(MatrixKey_GetValue()==9)
        {
          OLED_Clear_r();
          break;
        }
      }
      break;
        
      
    }
    break;
      
	default : break;
	};

		
		DS1302_Readtime();
		show_time(time_data);
		
		if(bell_data[0]==time_data[3] && bell_data[1]==time_data[4] && bell_data[2]==time_data[5])//��������
		{
			bell_onoff=1;
		}
		while(bell_flag && bell_onoff)
		{
		BEEP=!BEEP;
    delay_ms(1);
    if(MatrixKey_GetValue()==2)
      {
        bell_onoff=0;
        BEEP=0;
        break;        
      }
		}
		
	}
}


