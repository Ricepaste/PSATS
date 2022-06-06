void setup()
{
    // int
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(12, OUTPUT);
    // digitalWrite(12, HIGH);

    Serial.begin(115200);
}

// the loop function runs over and over again forever
String incomingByte = "";
void loop()
{
    if (Serial.available() > 0)
    {
        // read the incoming byte:
        incomingByte = Serial.readString();
        // say what you got:
        Serial.print("I received: ");
        Serial.println(incomingByte);

        if (incomingByte == "solar\n")
        {
            digitalWrite(LED_BUILTIN, HIGH);
            digitalWrite(12, HIGH);
            Serial.println("solar_mode is ON");
        }
        else if (incomingByte == "normal\n")
        {
            digitalWrite(LED_BUILTIN, LOW);
            digitalWrite(12, LOW);
            Serial.println("normal electricity mode is ON");
        }
    }
}
