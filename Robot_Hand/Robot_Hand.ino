#include <Servo.h> //서보 모터 라이브러리
#include <SoftwareSerial.h> // 블루투스 라이브러리


SoftwareSerial mySerial(12, 13); // RX, TX

Servo myservo1; //엄지 모터
Servo myservo2; //검지 모터
Servo myservo3; //중지 모터
Servo myservo4; //약지 모터
Servo myservo5; //소지 모터
Servo myservo6; //손바닥 모터

int control = 0; //블루투스,플렉스센서 구분

int flexValue1; //엄지 플렉스
int flexValue2; //검지 플렉스
int flexValue3; //중지 플렉스
int flexValue4; //약지 플렉스
int flexValue5; //소지 플렉스
int flexValue6; //손바닥 플렉스

int mc1;
int mc2;
int mc3;
int mc4;
int mc5;
int mc6;



void setup() {
  myservo1.attach(2);
  myservo1.write(180);

  myservo2.attach(3);
  myservo2.write(180);

  myservo3.attach(4);
  myservo3.write(180);

  myservo4.attach(5);
  myservo4.write(180);

  myservo5.attach(6);
  myservo5.write(180);

  myservo6.attach(7);
  myservo6.write(180);

  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop()
{

//----------- 앱인벤터----------------------------------
  if (mySerial.available()) 
  {
    control = 1; //플렉스 Disable
    char i = mySerial.read();
    switch (i)
    {

      case 'a':
        myservo1.write(0); //엄지 접기
        break;

      case '1':
        myservo1.write(180); //엄지 펴기
        control = 0;
        break;

      case 'b':
        myservo2.write(0); //검지 접기
        break;

      case '2':
        myservo2.write(180); //검지 펴기
        control = 0;
        break;

      case 'c':
        myservo3.write(0); //중지 접기
        break;

      case '3':
        myservo3.write(180); //중지 펴기
        control = 0;
        break;

      case 'd':
        myservo4.write(0); //약지 접기
        break;

      case '4':
        myservo4.write(180); //약지 펴기
        control = 0;
        break;

      case 'e':
        myservo5.write(0); //소지 접기
        break;

      case '5':
        myservo5.write(180); //소지 펴기
        control = 0;
        break;

      case 'f': //전체 접기
        myservo1.write(0);
        myservo6.write(90);
        myservo2.write(0);
        myservo3.write(0);
        //delay(300);
        myservo4.write(0);
        myservo5.write(0);
        
        break;
      case '6': //전체 펴기
        myservo1.write(180);
        myservo2.write(180);
        myservo3.write(180);
        myservo4.write(180);
        myservo5.write(180);
        myservo6.write(180);
        control = 0;
        break;
        }

  }

  if (control == 0) //플렉스 Enable
  {
    flexValue1 = analogRead(A1); //엄지 flex
    flexValue2 = analogRead(A2); //검지 flex
    flexValue3 = analogRead(A3); //중지 flex
    flexValue4 = analogRead(A4); //약지 flex
    flexValue5 = analogRead(A5); //소지 flex
    flexValue6 = analogRead(A6); //손바닥 flex

//---------------아날로그 값 범위 설정--------------------------------
    if (flexValue1 < 172)
      mc1 = 0;
    else
      mc1 = 180;

    if (flexValue2 < 190)
    {
      mc2 = 0;

    }
    else
      mc2 = 180;

    if (flexValue3 < 180)
      mc3 = 0;
    else
      mc3 = 180;

    if (flexValue4 < 220)
      mc4 = 0;
    else
      mc4 = 180;

    if (flexValue5 < 170)
      mc5 = 0;
    else
      mc5 = 180;

    if (flexValue6 < 120)
      mc6 = 90;
    else
      mc6 = 180;
//------------------------------------------------------------------

//---------------서보 모터 제어--------------------------------
    myservo1.write(mc1); //엄지
    myservo2.write(mc2); //검지
    myservo3.write(mc3); //중지
    myservo4.write(mc4); //약지
    myservo5.write(mc5); //소지
    myservo6.write(mc6); //손바닥
//----------------------------------------------------------------

//-------------아날로그 값, 서보모터 각도 모니터링--------------------------
    Serial.print("flex1: ");
    Serial.print(flexValue1);
    Serial.print("    ");
    Serial.print("엄지각도: ");
    Serial.print(mc1);
    Serial.print("    ");

    Serial.print("flex2: ");
    Serial.print(flexValue2);
    Serial.print("    ");
    Serial.print("검지각도: ");
    Serial.print(mc2);
    Serial.print("    ");

    Serial.print("flex3: ");
    Serial.print(flexValue3);
    Serial.print("    ");
    Serial.print("중지각도: ");
    Serial.print(mc3);
    Serial.print("    ");

    Serial.print("flex4: ");
    Serial.print(flexValue4);
    Serial.print("    ");
    Serial.print("약지각도: ");
    Serial.print(mc4);
    Serial.print("    ");

    Serial.print("flex5: ");
    Serial.print(flexValue5);
    Serial.print("    ");
    Serial.print("소지각도: ");

    Serial.print(mc5);
    Serial.print("    ");

    Serial.print("flex6: ");
    Serial.print(flexValue6);
    Serial.print("    ");
    Serial.print("손바닥각도: ");
    Serial.println(mc6);


    delay(50);
  }


}
