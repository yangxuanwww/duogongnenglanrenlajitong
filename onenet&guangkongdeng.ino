#define INTERVAL_SENSOR   17000             //定义传感器采样时间间隔  597000

#define INTERVAL_NET      17000             //定义发送时间

//传感器部分================================   

#include <Wire.h>                                  //调用库  

#include <ESP8266.h>





const int TrigPin = 4; //发送超声波
const int EchoPin = 5; //接收超声波
float cm;

#define SSID           "oppo"                   // cannot be longer than 32 characters!

#define PASSWORD       "lyrzuikeai"



#define IDLE_TIMEOUT_MS  3000      // Amount of time to wait (in milliseconds) with no data 

                                   // received before closing the connection.  If you know the server

                                   // you're accessing is quick to respond, you can reduce this value.



// WEBSITE



#define HOST_NAME   "api.heclouds.com"



// 修改成自己的ID

#define DEVICEID   "503154232"

#define PROJECTID "184236"

#define HOST_PORT   (80)



// 修改成自己在OneNet上面的apikey

// 大概长这样: VeFI0HZ44Qn5dZO14AuLbWSlSlI=

String apiKey="Runw5tlO0zk4IZxZ8bb1z648Szg=";

char buf[10];



#define INTERVAL_sensor 2000

unsigned long sensorlastTime = millis();





String mCottenData;

String jsonToSend;



//3,传感器值的设置 

float sensor_dis;               //传感器温度、湿度、光照   

char  sensor_dis_c[7] ;    //换成char数组传输



#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); /* RX:D3, TX:D2 */

ESP8266 wifi(mySerial);

//ESP8266 wifi(Serial1);                                      //定义一个ESP8266（wifi）的对象

unsigned long net_time1 = millis();                          //数据上传服务器时间

unsigned long sensor_time = millis();                        //传感器采样时间计时器



//int SensorData;                                   //用于存储传感器数据

String postString;                                //用于存储发送数据的字符串

//String jsonToSend;                                //用于存储发送的json格式参数

#include <OurSpark.h>                              //灯
#define Light_PIN A2
#define Light_value 25

const int buttonPin = 2;     
// 读取按键状态的变量
ColorLEDController LEDController1(1, 8);

int buttonState = 0;//初始化状态值  
int sensorValue;                                  //灯及触摸开关

void setup(void)     //初始化函数  

{       
 pinMode(buttonPin, INPUT)   ;           //触摸开关
  //初始化串口波特率  

    Wire.begin();

    Serial.begin(115200);   

    while(!Serial);
pinMode(TrigPin, OUTPUT);
pinMode(EchoPin, INPUT);



   //ESP8266初始化

    Serial.print("setup begin\r\n");   



  Serial.print("FW Version:");

  Serial.println(wifi.getVersion().c_str());



  if (wifi.setOprToStationSoftAP()) {

    Serial.print("to station + softap ok\r\n");

  } else {

    Serial.print("to station + softap err\r\n");

  }



  if (wifi.joinAP(SSID, PASSWORD)) {      //加入无线网

    Serial.print("Join AP success\r\n");  

    Serial.print("IP: ");

    Serial.println(wifi.getLocalIP().c_str());

  } else {

    Serial.print("Join AP failure\r\n");

  }



  if (wifi.disableMUX()) {

    Serial.print("single ok\r\n");

  } else {

    Serial.print("single err\r\n");

  }



  Serial.print("setup end\r\n");

    

  

}

void loop(void)     //循环函数  

{    
  digitalWrite(TrigPin, LOW);
delayMicroseconds(2);
digitalWrite(TrigPin, HIGH);
delayMicroseconds(10);
digitalWrite(TrigPin, LOW);
// 检测脉冲宽度，并计算出距离
cm = pulseIn(EchoPin, HIGH) / 58.0;
//通过串口监视器输出
Serial.print("Distance:"); Serial.println(cm);
delay(1000);

  if (sensor_time > millis())  sensor_time = millis();  

    

  if(millis() - sensor_time > INTERVAL_SENSOR)              //传感器采样时间间隔  

  {  

    getSensorData();                                        //读串口中的传感器数据

    sensor_time = millis();

  }  



    

  if (net_time1 > millis())  net_time1 = millis();

  

  if (millis() - net_time1 > INTERVAL_NET)                  //发送数据时间间隔

  {                

    updateSensorData();                                     //将数据上传到服务器的函数

    net_time1 = millis();

  }

  

}



void getSensorData(){  

    sensor_dis=cm;
    delay(1000);

    dtostrf(sensor_dis, 2, 1, sensor_dis_c);

    

}

void updateSensorData() {

  if (wifi.createTCP(HOST_NAME, HOST_PORT)) { //建立TCP连接，如果失败，不能发送该数据

    Serial.print("create tcp ok\r\n");



    jsonToSend="{\"Distance\":";

    dtostrf(sensor_dis,1,2,buf);

    jsonToSend+="\""+String(buf)+"\"";

    
    jsonToSend+="}";







    postString="POST /devices/";

    postString+=DEVICEID;

    postString+="/datapoints?type=3 HTTP/1.1";

    postString+="\r\n";

    postString+="api-key:";

    postString+=apiKey;

    postString+="\r\n";

    postString+="Host:api.heclouds.com\r\n";

    postString+="Connection:close\r\n";

    postString+="Content-Length:";

    postString+=jsonToSend.length();

    postString+="\r\n";

    postString+="\r\n";

    postString+=jsonToSend;

    postString+="\r\n";

    postString+="\r\n";

    postString+="\r\n";



  const char *postArray = postString.c_str();                 //将str转化为char数组

  Serial.println(postArray);

  wifi.send((const uint8_t*)postArray, strlen(postArray));    //send发送命令，参数必须是这两种格式，尤其是(const uint8_t*)

  Serial.println("send success");   

     if (wifi.releaseTCP()) {                                 //释放TCP连接

        Serial.print("release tcp ok\r\n");

        } 

     else {

        Serial.print("release tcp err\r\n");

        }

      postArray = NULL;                                       //清空数组，等待下次传输数据

  

  } else {

    Serial.print("create tcp err\r\n");

  }
 buttonState = digitalRead(buttonPin);//读取按键的状态
    Serial.println(buttonState);  //将状态输出到串口
    sensorValue = analogRead(Light_PIN);
    delay(10);    //延时一秒，'''可以设置为50，加快刷新数据的速率'''
    if(buttonState==0&&sensorValue < Light_value)
     {
      LEDController1.ShowColor(0,130,50,75);
      delay(3000);
      }
    else LEDController1.ShowColor(0,0,0,0);
  

}
