/*
 * File:          u3_exam_munoz_samara.c
 * Date:
 * Description:
 * Author:
 * Modifications:
 */

/*
 * You may need to add include files like <webots/distance_sensor.h> or
 * <webots/differential_wheels.h>, etc.
 */

///////LIBRERIAS//////////////
#include <webots/robot.h>
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/position_sensor.h>
#include <webots/distance_sensor.h>
#include <webots/keyboard.h>

//////LIBRERIA STANDARD//////////
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//////////MACROS////////////////
#define TIME_STEP 64
#define PI 3.1416
#define OBSTACLE_DISTANCE 200.0



///global variables////
int turn_left = 0;
int turn_right = 0;
int a = 1;
int m = 0;
double compare;
float angularVel, linealVel,RPM;

/////encoder//////////
double position = 0;
double c=0;
double posFinal;

////distance sensor////
double distance_left = 0;
double distance_right = 0;

/////keyboard//////////
int key;
  



int main(int argc, char **argv)
{
  /* necessary to initialize webots stuff */
  wb_robot_init();
  wb_keyboard_enable(TIME_STEP);


  WbDeviceTag wheel_1 = wb_robot_get_device("wheel1");
  WbDeviceTag wheel_2 = wb_robot_get_device("wheel2");
  WbDeviceTag wheel_3 = wb_robot_get_device("wheel3");

  WbDeviceTag disleft = wb_robot_get_device("ds_left");
  WbDeviceTag disright = wb_robot_get_device("ds_right");


  WbDeviceTag pos1 = wb_robot_get_device("ps_1");
  WbDeviceTag pos2 = wb_robot_get_device("ps_2");
  WbDeviceTag pos3 = wb_robot_get_device("ps_3");


  wb_distance_sensor_enable(disleft,TIME_STEP);
  wb_distance_sensor_enable(disright,TIME_STEP);



  wb_position_sensor_enable(pos1,TIME_STEP);
  wb_position_sensor_enable(pos2,TIME_STEP);
  wb_position_sensor_enable(pos3,TIME_STEP);

  wb_motor_set_position(wheel_1,INFINITY);
  wb_motor_set_position(wheel_2,INFINITY);
  wb_motor_set_position(wheel_3,INFINITY);
  
  
  printf(" 'Up Arrow' to move forward linearly at 0.3 m/s\n");
  printf(" 'Down Arrow' to move backward linearly at 0.3 m/s\n");
  printf(" 'Left Arrow' to move linearly to the left at 0.3 m/s\n");
  printf(" 'Right Arrow'to move linearly to the right at 0.3 m/s\n");
  printf(" 'A' key to turn the robot left at 45 degrees/s\n");
  printf(" 'S' key to turn the robot right at 45 degrees/s\n");
  printf(" 'G' key to start Autonomous Mode for the robot\n");
  printf(" 'W' key to start Manual Mode\n");
  fflush(stdout);
  
  
  void Manual(){

    //Read Distance Sensor//
    distance_left = (wb_distance_sensor_get_value(disleft)*0.2)/65535;
    distance_right = (wb_distance_sensor_get_value(disright)*0.2)/65535;


    //Read Position Sensor//
    position = wb_position_sensor_get_value(pos1);

    //Print Read Values//

     printf("distance_left: %lf\r\n", distance_left);
     printf("distance_right: %lf\r\n", distance_right);
     printf("Encoder Postion: %lf\r\n", position);

      wb_motor_set_velocity(wheel_1, 0);
      wb_motor_set_velocity(wheel_2, 0);
      wb_motor_set_velocity(wheel_3, 0);
    
   

    if(key==WB_KEYBOARD_UP){

      wb_motor_set_position(wheel_1, INFINITY);
      wb_motor_set_velocity(wheel_1, -5);
      wb_motor_set_position(wheel_2, INFINITY);
      wb_motor_set_velocity(wheel_2, 5);
      wb_motor_set_position(wheel_3, INFINITY);
      wb_motor_set_velocity(wheel_3, 0);
      }

    if(key==WB_KEYBOARD_DOWN){

      wb_motor_set_position(wheel_1, INFINITY);
      wb_motor_set_velocity(wheel_1, 5);
      wb_motor_set_position(wheel_2, INFINITY);
      wb_motor_set_velocity(wheel_2, -5);
      wb_motor_set_position(wheel_3, INFINITY);
      wb_motor_set_velocity(wheel_3, 0);
      }

      if(key==WB_KEYBOARD_LEFT){

      wb_motor_set_position(wheel_1, INFINITY);
      wb_motor_set_velocity(wheel_1, -4);
      wb_motor_set_position(wheel_2, INFINITY);
      wb_motor_set_velocity(wheel_2, -4);
      wb_motor_set_position(wheel_3, INFINITY);
      wb_motor_set_velocity(wheel_3, 8);
      }

      if(key==WB_KEYBOARD_RIGHT){

      wb_motor_set_position(wheel_1, INFINITY);
      wb_motor_set_velocity(wheel_1, 4);
      wb_motor_set_position(wheel_2, INFINITY);
      wb_motor_set_velocity(wheel_2, 4);
      wb_motor_set_position(wheel_3, INFINITY);
      wb_motor_set_velocity(wheel_3, -8);
      }

      
      //right 45 degrees//
      if(key == 'S' ){
      compare = position + 0.785398; //0.7853... = 45 degrees to the left
      turn_left = 1;
      }

      if(turn_left == 1){

          if(position <= compare){
            wb_motor_set_velocity(wheel_1, 5);
            wb_motor_set_velocity(wheel_2, 5);
            wb_motor_set_velocity(wheel_3, 5);
            }

          else{
            wb_motor_set_velocity(wheel_1, 0);
            wb_motor_set_velocity(wheel_2, 0);
            wb_motor_set_velocity(wheel_3, 0);
            turn_left = 0;
            }
      }

      //left 45 degrees//
      if(key == 'A' ){
      compare = position - 0.785398; //0.7853... = 45 degrees to the left
      turn_right = 1;
      }

        if(turn_right == 1){
  
            if(position >= compare){
              wb_motor_set_velocity(wheel_1, -5);
              wb_motor_set_velocity(wheel_2, -5);
              wb_motor_set_velocity(wheel_3, -5);
              }
  
            else{
              wb_motor_set_velocity(wheel_1, 0);
              wb_motor_set_velocity(wheel_2, 0);
              wb_motor_set_velocity(wheel_3, 0);
              turn_right = 0;
              }
              
              
         }
       }
       
   
   
   
   void Automatic(){
   
       
      //Read Distance Sensor//
      distance_left = (wb_distance_sensor_get_value(disleft)*0.2)/65535;
      distance_right = (wb_distance_sensor_get_value(disright)*0.2)/65535;
  
  
      //Read Position Sensor//
      position = wb_position_sensor_get_value(pos1);
      posFinal = position-c ;
      c = position;
      
      
      linealVel= (( posFinal/0.064)*0.06);
      angularVel= ( posFinal/0.064);
      RPM =( posFinal*60)/(2*PI);
      
      //RPM =(compare/0.064)*(60/(2*3.1416));
      
       //Print Read Values//
  
       printf("distance_left: %lf\r\n", distance_left);
       printf("distance_right: %lf\r\n", distance_right);
       printf("Encoder1: %f\r\n", position);
       printf("Linear Velocity: %f\r\n", linealVel);
       printf("Angular Velocity: %f\r\n", angularVel);
       printf("RPM: %f\r\n", RPM);
       
       
    
       wb_motor_set_velocity(wheel_1, -6.66);
       wb_motor_set_velocity(wheel_2, 6.66);
       wb_motor_set_velocity(wheel_3, 0);

       if(distance_left < distance_right && distance_left < OBSTACLE_DISTANCE){

        wb_motor_set_velocity(wheel_1, 0);
        wb_motor_set_velocity(wheel_2, 6.66);
        wb_motor_set_velocity(wheel_3, -6.66);
    
       }
       else if(distance_left > distance_right && distance_right < OBSTACLE_DISTANCE){
    
        wb_motor_set_velocity(wheel_1, 0);
        wb_motor_set_velocity(wheel_2, -6.66);
        wb_motor_set_velocity(wheel_3, 6.66);
      }
    
    }

    
      
while (wb_robot_step(TIME_STEP) != -1) {
     key = wb_keyboard_get_key();

      if(key == 'W'){
        m = 1;
        a = 0;
        printf("Manual mode \n");
      }
    
    
      else if (key == 'G'){
        a = 1;
        m = 0;
       printf("Automatic mode \n");
    
      }
    
      if(m == 1){
      Manual();
      }
      if(a == 1){
      Automatic();
      }
    
  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}
