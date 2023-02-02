# 自主プロ
「上がれ」というと、ほうきの末端についているモータが回転して、手元にほうきの柄が上がってくるものを作った。

## 実行環境
- Ubuntu 18.04
- Python 2.7
- Arduino Nano Every
- Arduino 1.8.13
- ROS Melodic

## 環境導入
- Julius ROS
```
$ sudo apt install ros-melodic-julius-ros
```
- ros speech recognition
```
$ sudo apt install ros-melodic-ros-speech-recognition
```

## 実行方法
1.音声認識ノードの立ち上げ
```
roslaunch ros_speech_recognition speech_recognition.launch language:=ja-JP device:=hw:0,0 sample_rate:=44100 n_channel:=2 launch_sound_play:=false continuous:=true
```
を実行する。

2. speech_listener.pyの実行
「上がれ」という音声を認識したときに/speechというトピックにstd_msgs::UInt16型の"data:1"というメッセージを流して、「下がれ」という音声のときには"data:2"というメッセージを流す。

3. jishupro_agare.inoをArduino Nano Everyに書き込む。
このときに使用しているKondo Servoの変換基板が書き込みモードになっているかを確認し、書き込んだ後は実行モードに変更する。

4. ros serialの通信を開始する
3で書き込んだ際に、ポートが何になっているかを確認（Ubuntu環境であれば/dev/ttyACM0か/dev/ttyACM1など）し、それにあったlaunchファイルを起動する。例えば、/dev/ttyACM0のときは
```
roslaunch mechatrobot jishupro_acm0.launch
```
を実行する。また、このlaunchファイルを使用しなくても、
```
rosrun rosserial_python serial_node.py _port:=/dev/ttyACM0 _baud:=9600
```
をすることでノードを起動することができる。

これらが実行できれば、うまく行けば「上がれ」でモータが動くはずである。
