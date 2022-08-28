void setup()
{
    // int
    // initialize digital pin LED_BUILTIN as an output.
    for (int i = 2; i < 13; i++)
    {
        pinMode(i, OUTPUT);
    }
    // digitalWrite(12, HIGH);

    Serial.begin(115200);
}

// the loop function runs over and over again forever
String incomingByte = "";
double ap;
double voltage;
bool Automatic_mode = false;
void loop()
{
    if (Serial.available() > 0)
    {
        incomingByte = Serial.readString();
        Serial.print("I received: ");
        Serial.println(incomingByte);
        if (incomingByte == "s\n")
        {
            solar_mode();
        }
        else if (incomingByte == "n\n")
        {
            normal_mode();
        }
    }
    delay(2000);
}

void normal_mode()
{
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);

    Serial.println("normal electricity mode is ON");
    Automatic_mode = false;
}

void solar_mode()
{
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    Serial.println("solar_mode is ON");
    Automatic_mode = true;
}