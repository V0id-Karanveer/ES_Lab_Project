#include<LPC17xx.h>
#include<stdio.h>

unsigned long int temp1=0, temp2=0 ;
#define RS_CTRL  0x00000100  //P0.8
#define EN_CTRL  0x00000200  //P0.9
#define DT_CTRL  0x00000FF0  //P0.4 to P0.7 data lines



void lcd_init(); // initialisation
void wr_cn(); //write command portwrite
void clr_disp(); //clear display command 0x01
void delay_lcd(unsigned int); //for loop delay 
void lcd_com(); // lcd write for command               
void wr_dn(); // port_write for data
void lcd_data(); // lcd write for data
void clear_ports(); //clr rs , en , data
void lcd_puts(char *);// call lcd_data fn while writing



int main(void){
char Msg[] = {"Moisture:"};
SystemInit();
SystemCoreClockUpdate();
lcd_init();

}



void lcd_init()
{

   LPC_PINCON->PINSEL0 &= 0x00000000; 




    LPC_GPIO0->FIODIR |= DT_CTRL;
    LPC_GPIO0->FIODIR |= RS_CTRL; 
    LPC_GPIO0->FIODIR |= EN_CTRL;    

    clear_ports();




    temp2 = (0x30);
    wr_cn();     

    temp2 = (0x30);
    wr_cn();

    temp2 = (0x30);
    wr_cn();



    temp2 = (0x20);
    wr_cn();

		temp1 = 0x28; 
    lcd_com();

    temp1 = 0x0c;    
    lcd_com();

    temp1 = 0x06;
    lcd_com();

    temp1 = 0x01;
    lcd_com();

    temp1 = 0x80;
    lcd_com();
    return;
}



void lcd_com(void)
{
    temp2 = temp1 & 0xf0;
    wr_cn();
    temp2 = temp1 & 0x0f; 
    temp2 = temp2 << 4; 
    wr_cn();
    delay_lcd(1000);
    return;
}

 


void wr_cn(void)                        
{      
    clear_ports();
    LPC_GPIO0->FIOPIN = temp2;    
    LPC_GPIO0->FIOCLR = RS_CTRL;        
    LPC_GPIO0->FIOSET = EN_CTRL;       
    delay_lcd(25);
    LPC_GPIO0->FIOCLR  = EN_CTRL;    
    return;

}

 

void lcd_data(void)
{             
    temp2 = temp1 & 0xf0;
    wr_dn();
    temp2= temp1 & 0x0f;    
    temp2= temp2 << 4;
    wr_dn();
    delay_lcd(1000);    
    return;
}

 

void wr_dn(void)
{        
    clear_ports();

 

    LPC_GPIO0->FIOPIN = temp2;         
    LPC_GPIO0->FIOSET = RS_CTRL;    
    LPC_GPIO0->FIOSET = EN_CTRL;       
    delay_lcd(25);
    LPC_GPIO0->FIOCLR = EN_CTRL;    
    return;
}

 

void delay_lcd(unsigned int r1)
{
      unsigned int r;
      for(r=0;r<r1;r++);
    return;
}

 

void clr_disp(void)
{
    temp1 = 0x01;
    lcd_com();
    return;
}
void clear_ports(void)
{

    LPC_GPIO0->FIOCLR = DT_CTRL; 
    LPC_GPIO0->FIOCLR = RS_CTRL;  
    LPC_GPIO0->FIOCLR = EN_CTRL; 

    return;
}

 

void lcd_puts(char *buf1){

   unsigned int i=0;

 

   while(buf1[i]!='\0'){

         temp1 = buf1[i];
     lcd_data();
         i++;

     if(i==27){
             temp1 = 0xc0;
             lcd_com();
         }   
   }
    return;
}