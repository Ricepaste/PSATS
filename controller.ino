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
double ap;
double voltage;
bool Automatic_mode = false;
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
            solar_mode();
        }
        else if (incomingByte == "normal\n")
        {
            normal_mode();
        }
    }
    // Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n");
    ap = analogRead(A0);
    ap = (ap - 505.) * 0.02;
    Serial.println("LED current consumption: " + String(ap) + "A");
    ap = analogRead(A1);
    ap = (ap - 505.) * 0.02;
    Serial.println("USB hub current consumption: " + String(ap) + "A");
    voltage = analogRead(A2) / 68 * 1.67;
    Serial.println("solar panel voltage : " + String(voltage) + "V");

    if (Automatic_mode && voltage < 9.0)
    {
        normal_mode();
        Automatic_mode = true;
    }
    else if (Automatic_mode && voltage >= 9.0)
    {
        solar_mode();
    }

    delay(2000);
}

void normal_mode()
{
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(12, LOW);
    Serial.println("normal electricity mode is ON");
    Automatic_mode = false;
}

void solar_mode()
{
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(12, HIGH);
    Serial.println("solar_mode is ON");
    Automatic_mode = true;
}