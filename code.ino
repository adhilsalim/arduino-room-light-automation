const int echoPin = 8;
const int trigPin = 9;
const int ledPin = 13;
const int ldrPin = A0;

int distance;
long duration;
int ldrStatus;
int ledStatus;

int presentInRoom = 0;

void setup()
{
    Serial.begin(9600);

    Serial.println("Serial Communication Started.");
    blinkLed();

    pinMode(echoPin, INPUT);
    pinMode(ldrPin, INPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(ledPin, OUTPUT);

    Serial.println("Turning off room light.");
    blinkLed();
    digitalWrite(ledPin, LOW);
    ledStatus = 0;
}

void loop()
{
    ldrStatus = analogRead(ldrPin);

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = (duration * 0.034) / 2;

    checkMotion();
    setLightStatus();
}

void checkMotion()
{
    if (distance <= 15)
    {
        Serial.print("Motion Detected ");
        Serial.print(presentInRoom == 1 ? "[OUT]\n" : "[IN]\n");
        toggleRoomStatus();
    }
}

void toggleRoomStatus()
{

    if (presentInRoom == 1)
    {
        presentInRoom = 0;
    }
    else
    {
        presentInRoom = 1;
    }
    setLightStatus();
    delay(1600);
}

void setLightStatus()
{
    if (presentInRoom == 1 && ldrStatus <= 300)
    {

        if (ledStatus != 1)
        {
            digitalWrite(ledPin, HIGH);
            Serial.println("Room Light ON");
            ledStatus = 1;
        }
    }
    else
    {

        if (ledStatus == 1)
        {
            digitalWrite(ledPin, LOW);
            Serial.println("Room Light OFF");
            ledStatus = 0;
        }
    }
}

void blinkLed()
{
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
}