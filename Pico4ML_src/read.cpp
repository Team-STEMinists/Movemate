//#include "ICM20948.h"
#include <string.h>
#include "stdio.h"
#include <string.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>
//#include "accelerometer_handler.h"
#include <ICM42622.h>
#include <pico/stdio.h>
#include "UART_TxRx.h"
#include "LCD_st7735.h"
#include <math.h>

/*bool detect_movement(uint32_t ms,int per){
  float Ax1, Ay1, Az1,Ax2, Ay2, Az2;
  if(ICM42622::Icm42622DataReady()){
      ICM42622::Icm42622ReadAccel(&Ax1,&Ay1,&Az1);
      sleep_ms(ms);
      ICM42622::Icm42622ReadAccel(&Ax2,&Ay2,&Az2);
      float per1 = (Ax2-Ax1)*100/Ax1;
      float per2 = (Ay2-Ay1)*100/Ay1;
      float per3 = (Az2-Az1)*100/Az1;
      if(per1 > per || per2 > per || per3 > per){
        
      }

  }
  
}*/

int get_the_reps_in(){
  float Gx,Gy,Gz;
  bool arr[5000];
  float data[5000];
  int rep_counter = 0;
  char rep_str[20];
  if(ICM42622::Icm42622DataReady()){
    for(int i=0;i<5000;i++){
    ICM42622::Icm42622ReadGyro(&Gx,&Gy,&Gz);
    data[i] = Gx;
    sleep_ms(4);
    }
    long double mean=0.0;
    for (int i = 0; i < 5000; i++) {     
       mean = mean + data[i];    
    }
    printf("mean_tatol:%f",mean);
    mean = mean/5000.0;
    for(int i=0;i<5000;i++){
    arr[i] = (data[i] <= mean) ? 0 : 1;
    }
    for(int i=1;i<5000;i++){
      if(arr[i] > arr[i-1]){
      rep_counter++; 
    }
    }
    sprintf(rep_str,"%d",rep_counter);
    ST7735_WriteString(30, 70,rep_str , Font_11x18, ST7735_BLACK, ST7735_GREEN);
    printf("rep:%d",rep_counter);
  
  }
  return rep_counter;
}

int get_the_reps_in2(){
  ST7735_FillScreen(ST7735_GREEN);
  float Gx,Gy,Gz,Ax,Ay,Az;
  bool arr[7500];
  float data[7500];
  int rep_counter = 0;
  char rep_str[20];
  float Ay_min=0,Ay_max=0,Az_min=0,Az_max=0;
  if(ICM42622::Icm42622DataReady()){
    for(int i=1;i<7500;i++){
    ICM42622::Icm42622ReadGyro(&Gx,&Gy,&Gz);
    ICM42622::Icm42622ReadAccel(&Ax,&Ay,&Az);
    data[i] = Gx;
    if(Ay<Ay_min)
      Ay_min = Ay;
    if(Ay>Ay_max)
      Ay_max = Ay;
    if(Az<Az_min)
      Az_min = Az;
    if(Az>Az_max)
      Az_max = Az;
    arr[i] = (Gx <= 50) ? 0 : 1;
    if(arr[i] > arr[i-1]){
      rep_counter++;
      sprintf(rep_str,"%d",rep_counter);
      ST7735_WriteString(30, 70,rep_str , Font_11x18, ST7735_BLACK, ST7735_GREEN);
      printf("\nrep:%d",rep_counter);
      UART_TR::U_tx("[I:");
      UART_TR::U_tx(rep_str);
      UART_TR::U_tx("]");
    }
    sleep_ms(4);
    }

    printf("\nThe Exercise is:%s",((Ay_max-Ay_min)>2.1 && (Az_max-Az_min)>2.1 ? "Bicep" : "Lateral Raises"));
    UART_TR::U_tx("[W:");
    if(rep_counter < 5)
      UART_TR::U_tx("Not enough data to detect");
    else if((Ay_max-Ay_min)>2.1 && (Az_max-Az_min)>2.1)
      UART_TR::U_tx("Bicep Curls");
    else
      UART_TR::U_tx("Lateral Raises");
    UART_TR::U_tx("]");
    //float diff_Ay,diff_Az;
    printf("Difference Ay:%f\nDifference Az:%f\n",Ay_max-Ay_min,Az_max-Az_min);
    
  }
  return rep_counter;
}

bool detect_movement_stationery(int ms,int per){
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
  else
    return false;
}

bool detect_movement(int ms,int per){
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
          if(per2 > per || per3 > per){
            count++;    
      }
      }
      if(count == 5)
        return true;
      else
        count = 0;
      }
  }
  else
    return false;
}
int main(){
  stdio_init_all();
  i2c_init(I2C_PORT, 400 * 1000);
  gpio_set_function(4, GPIO_FUNC_I2C);
  gpio_set_function(5, GPIO_FUNC_I2C);
  gpio_pull_up(4);
  gpio_pull_up(5);
  sleep_ms(1000);
  ST7735_Init();
  //ST7735_DrawImage(0, 0, 80, 160, arducam_logo);
  ST7735_FillScreen(ST7735_GREEN);
  ST7735_DrawImage(0, 0, 80, 40, (uint8_t *)IMU_ICM20948);

  ST7735_WriteString(5, 45, "WElcome", Font_11x18, ST7735_BLACK, ST7735_GREEN);
  ST7735_WriteString(30, 70, "Land", Font_11x18, ST7735_BLACK, ST7735_GREEN);
  ICM42622::Icm42622Init();
  UART_TR::UART_init(0,1,9600);
  char tag = '0';
  int rep;
  sleep_ms(5000);
  //Initialize the GUI
  UART_TR::U_tx("[R:0]");
  while(1){
    //printf("The Reps are:%d",get_the_reps_in2());

    //Read the RFID Tag
    tag = UART_TR::U_rx();
    UART_TR::U_tx("[ID:");
    if(tag == '1')
      UART_TR::U_tx("Saurabh");
    else if(tag == '2')
      UART_TR::U_tx("Essa");
    else
      UART_TR::U_tx("Amogh");
    UART_TR::U_tx("]");

    //Start Exercise Detection and Counting
    UART_TR::U_tx("[R:1]");
    rep = get_the_reps_in2();
    sleep_ms(10000);
    UART_TR::U_tx("[R:0]");

    

    //sleep_ms(5000);
    //printf("%d\n",detect_movement_stationery(50,10));
    /*if(detect_movement_stationery(50,10)){
      ST7735_WriteString(30, 70, "Stat", Font_11x18, ST7735_BLACK, ST7735_GREEN);
    }
    else if(detect_movement(10,20)){
      ST7735_WriteString(30, 70, "Move", Font_11x18, ST7735_BLACK, ST7735_GREEN);
    }*/
    
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








    /*float Ax, Ay, Az,Gx,Gy,Gz;
    char operation;
    int sample_size = 2500;
    float AX[sample_size],AY[sample_size],AZ[sample_size],GX[sample_size],GY[sample_size],GZ[sample_size];
    if(ICM42622::Icm42622DataReady()){
      scanf(" %c",&operation);
      if(operation == 'r'){
        for(int i=0;i<sample_size;i++){
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
      for(int i=0;i<sample_size;i++){
        printf("%f,",AX[i]);
      }
      printf("],[Ay,");
      for(int i=0;i<sample_size;i++){
        printf("%f,",AY[i]);
      }
      printf("],[Az,");
      for(int i=0;i<sample_size;i++){
        printf("%f,",AZ[i]);
      }
      printf("],[Gx,");
      for(int i=0;i<sample_size;i++){
        printf("%f,",GX[i]);
      }
      printf("],[Gy,");
      for(int i=0;i<sample_size;i++){
        printf("%f,",GY[i]);
      }
      printf("],[Gz,");
      for(int i=0;i<sample_size;i++){
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
    //}
  }
}





