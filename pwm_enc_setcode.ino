#define encoder0PinA  2
#define encoder0PinB  3

volatile long int encoder0Pos = 0;

int read;
int set_pwm = 255;
int motor_pwm = 0;


long int prev_encoder = 0;
int delta_cnt = 0;
float speed_cnt = 0;
float speed_rpm = 0;

void setup() {// Motor PWM Pins
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  // Encoder PULLUP Pins
  pinMode(encoder0PinA, INPUT_PULLUP);
  pinMode(encoder0PinB, INPUT_PULLUP);

  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoderA, RISING);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
  {  
    //Serial.println(read);
    read = Serial.parseInt();
    if (read >= 0 && read <= 255)
    {
      set_pwm = read;
      motor_pwm = set_pwm;
      //Serial.println(motor_pwm);
      analogWrite(5, motor_pwm);
      analogWrite(6, 0);
    }
    else if (read <= 0  && read >= -255)
    {
      set_pwm = read;
      motor_pwm = set_pwm;
      //Serial.println(motor_pwm);
      analogWrite(6, motor_pwm);
      analogWrite(5, 0);
    }
    else
    {
      
    }
  }
  delta_cnt = (int)(encoder0Pos - prev_encoder);
  speed_cnt = delta_cnt * 100;
  speed_rpm = speed_cnt * 0.1;
  prev_encoder = encoder0Pos;
  Serial.println (speed_rpm, 3);
  delay(10);
}

void doEncoderA() {
  // look for a low-to-high on channel A
    // check channel B to see which way encoder is turning
  if (digitalRead(encoder0PinB) == LOW) {
    encoder0Pos = encoder0Pos + 1;         // CW
  }
  else {
    encoder0Pos = encoder0Pos - 1;         // CCW
  }
}
