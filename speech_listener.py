#!/usr/bin/env python
# coding=utf-8
import rospy
# from std_msgs.msg import Bool
from std_msgs.msg import UInt16
from speech_recognition_msgs.msg import *
from speech_recognition_msgs.srv import *

def cb(msg):
    pub = rospy.Publisher('speech', UInt16)
    uint16_msg = UInt16()
    rospy.loginfo(msg.transcript[0])
    
    if msg.transcript[0] in ["上がれ", "暴れ", "剥がれ", "agar", "流れ"]:
        print("上がれ")
        uint16_msg.data = 1
        pub.publish(uint16_msg)

    elif msg.transcript[0] == "下がれ":
        print("下がれ")
        uint16_msg.data = 2
        pub.publish(uint16_msg)
        
def main():
    rospy.init_node('speech_listener', anonymous=True)
    rospy.Subscriber("/Tablet/voice", SpeechRecognitionCandidates, cb)
    rospy.loginfo("Setting up vocabulary ... ")

    try:
        rospy.loginfo("good")
    except rospy.ServiceException, e:
        print("Service call failed: %s"%e)
        rospy.loginfo("OK")

    rate = rospy.Rate(10)
    
    rospy.spin()
    rate.sleep()

if __name__ == '__main__':
    main()

