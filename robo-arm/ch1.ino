/*
 * rosserial Servo Control Example
 *
 * This sketch demonstrates the control of hobby R/C servos
 * using ROS and the arduiono
 * 
 * For the full tutorial write up, visit
 * www.ros.org/wiki/rosserial_arduino_demos
 *
 * For more information on the Arduino Servo Library
 * Checkout :
 * http://www.arduino.cc/en/Reference/Servo
 */

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include <WProgram.h>
#endif

#include <Servo.h> 
#include <ros.h>
#include <std_msgs/UInt16.h>

ros::NodeHandle  nh;

Servo servo_1;
Servo servo_2;
Servo servo_3;

void servo_cb_1( const std_msgs::UInt16& cmd_msg){
  servo_1.write(cmd_msg.data); //set servo angle, should be from 0-180  
  digitalWrite(13, HIGH-digitalRead(13));  //toggle led  
}

void servo_cb_2( const std_msgs::UInt16& cmd_msg){
  servo_2.write(cmd_msg.data); //set servo angle, should be from 0-180  
  digitalWrite(14, HIGH-digitalRead(14));  //toggle led  
}

void servo_cb_3( const std_msgs::UInt16& cmd_msg){
  servo_3.write(cmd_msg.data); //set servo angle, should be from 0-180  
  digitalWrite(15, HIGH-digitalRead(14));  //toggle led  
}
ros::Subscriber<std_msgs::UInt16> sub_1("servo_1", servo_cb_1);
ros::Subscriber<std_msgs::UInt16> sub_2("servo_2", servo_cb_2);
ros::Subscriber<std_msgs::UInt16> sub_3("servo_3", servo_cb_3);

void setup(){
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);


  nh.initNode();
  nh.subscribe(sub_1);
  nh.subscribe(sub_2);
  nh.subscribe(sub_3);
  
  servo_1.attach(9); //attach it to pin 9
  servo_2.attach(10); //attach it to pin 9
  servo_3.attach(11); //attach it to pin 9
}

void loop(){
  nh.spinOnce();
  delay(1);
}