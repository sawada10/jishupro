#include <ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Empty.h>

#include <IcsHardSerialClass.h>

ros::NodeHandle nh;
const byte EN_PIN = 2;
const long BAUDRATE = 115200;
const int TIMEOUT = 1000;
int cnt = 0;


IcsHardSerialClass krs(&Serial1,EN_PIN,BAUDRATE,TIMEOUT); 

void messageCb( const std_msgs::UInt16& msg){
  if(msg.data == 1){
      krs.setPos(8,10000);
  } else {
      krs.setPos(8,7500);
  }
}

ros::Subscriber<std_msgs::UInt16> sub_speech("speech", &messageCb);
void messageCb( const std_msgs::Empty& toggle_msg){
  nh.loginfo("led");
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
}

ros::Subscriber<std_msgs::Empty> sub("toggle_led", &messageCb );


void setup() {
  // put your setup code here, to run once:
  // pinMode(2, OUTPUT);
    pinMode(13, OUTPUT);
   
  nh.getHardware()->setBaud(9600);
  nh.initNode();
  nh.subscribe(sub);
  nh.subscribe(sub_speech);


  //wait until you are actually connected
  while (!nh.connected())
  {
      nh.loginfo("waiting");
     nh.spinOnce();
     delay(100);
  }

  krs.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  nh.spinOnce();
}
