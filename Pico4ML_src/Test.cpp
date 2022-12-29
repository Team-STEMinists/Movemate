//#include "ICM20948.h"
#include <string.h>
#include "stdio.h"
#include <string.h>
#include <math.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>
//#include "accelerometer_handler.h"
#include <ICM42622.h>
#include <pico/stdio.h>
#include "UART_TxRx.h"

bool detect_movement_stationery(uint32_t ms,int per){
  float Ax1, Ay1, Az1,Ax2, Ay2, Az2,per1,per2,per3;
  if(ICM42622::Icm42622DataReady()){
      int count = 0;
      while(1){
      ICM42622::Icm42622ReadAccel(&Ax1,&Ay1,&Az1);
      sleep_ms(ms);
      ICM42622::Icm42622ReadAccel(&Ax2,&Ay2,&Az2);
      per1 = abs(Ax2-Ax1)*100/abs(Ax1);
      per2 = abs(Ay2-Ay1)*100/abs(Ay1);
      per3 = abs(Az2-Az1)*100/abs(Az1);
      for(int i=0;i<10;i++){
          ICM42622::Icm42622ReadAccel(&Ax1,&Ay1,&Az1);
          sleep_ms(ms);
          ICM42622::Icm42622ReadAccel(&Ax2,&Ay2,&Az2);
          per1 = abs(Ax2-Ax1)*100/abs(Ax1);
          per2 = abs(Ay2-Ay1)*100/abs(Ay1);
          per3 = abs(Az2-Az1)*100/abs(Az1);
          if(per1 < per || per2 < per || per3 < per){
            count++;    
      }
      }
      if(count == 10)
        return true;
      else
        count = 0;
      }
      

  }
  
}

int main(){
  stdio_init_all();
  i2c_init(I2C_PORT, 400 * 1000);
  gpio_set_function(4, GPIO_FUNC_I2C);
  gpio_set_function(5, GPIO_FUNC_I2C);
  gpio_pull_up(4);
  gpio_pull_up(5);
  sleep_ms(1000);
  ICM42622::Icm42622Init();
  //UART_TR::UART_init(0,1,9600);
      char tag = '0';
  while(1){
    char open_bracket[] = "[";
    //UART_TR::U_tx(q);
    //tag = '0';
    /*tag = UART_TR::U_rx();
    printf("%c",tag);
    if(tag == '1')
      printf("Dolphin");
    else
      printf("Dalton");
    */
    //UART_TR::U_tx(&tag);
    float Ax, Ay, Az,Gx,Gy,Gz;
    char operation;
    float AX[512],AY[512],AZ[512],GX[512],GY[512],GZ[512];
    if(ICM42622::Icm42622DataReady()){
      scanf(" %c",&operation);
      if(operation == 'r'){
        for(int i=0;i<512;i++){
          ICM42622::Icm42622ReadGyro(&Gx,&Gy,&Gz);
          ICM42622::Icm42622ReadAccel(&Ax,&Ay,&Az);
          sleep_ms(4);
          AX[i] = Ax;
          AY[i] = Ay;
          AZ[i] = Az;
          GX[i] = Gx;
          GY[i] = Gy;
          GZ[i] = Gz;
        }
      }
      printf("{[Ax,");
      ///printf("%s:%s:%s\n",buf_x,buf_y,buf_z);
      for(int i=0;i<512;i++){
        printf("%f,",AX[i]);
      }
      printf("],[Ay,");
      for(int i=0;i<512;i++){
        printf("%f,",AY[i]);
      }
      printf("],[Az,");
      for(int i=0;i<512;i++){
        printf("%f,",AZ[i]);
      }
      printf("],[Gx,");
      for(int i=0;i<512;i++){
        printf("%f,",GX[i]);
      }
      printf("],[Gy,");
      for(int i=0;i<512;i++){
        printf("%f,",GY[i]);
      }
      printf("],[Gz,");
      for(int i=0;i<512;i++){
        printf("%f,",GZ[i]);
      }
      printf("]}");
    //printf("Wow");
      
      /*const float norm_x = -y;
      const float norm_y = x;
      const float norm_z = -z;*/
      /*char buf_x[7],buf_y[7],buf_z[7];
      sprintf (buf_x, "%f", norm_x);
      sprintf (buf_y, "%f", norm_y);
      sprintf (buf_z, "%f", norm_z);*/
      
      //UART_TR::U_tx("[");
      //UART_TR::U_tx(buf_x);
    }
  }
}





