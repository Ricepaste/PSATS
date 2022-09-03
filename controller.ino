// Arduino的初始設定
// 此處設定編號2~13的腳位全部以輸出的方式初始化
// 設定與電腦的溝通頻率為115200hz
void setup()
{
    for (int i = 2; i < 14; i++)
    {
        pinMode(i, OUTPUT);
    }
    Serial.begin(115200);
}

// Arduino的迴圈，以下的程式會不停重複執行直到關機
void loop()
{
    // 宣告後面會需要用到的變數
    int counter = 0;
    long long last, now;
    double voltage, voltage_sum;

    // 設定開始累加計算平均電壓的時間
    last = millis();
    counter = 0;
    voltage_sum = 0.0;

    do
    {
        // 設定現在的時間，若以累加計算電壓一秒後離開迴圈，並計算0.8秒內的平均電壓
        now = millis();

        // 以下是舊版的電壓計數據轉伏特的公式
        // voltage = analogRead(A2);
        // voltage = analogRead(A2) * 0.0198333333333333;
        voltage = analogRead(A2) * analogRead(A2) * (-0.000000585) + analogRead(A2) * 0.020823;
        voltage_sum += voltage;
        counter++;
    } while (now - last < 800);

    // 檢查目前的公共電力供電情形，並調整供電方針
    power_check(voltage_sum, counter);
}

// 一般供電模式
void normal_mode(int B_voltage, int counter)
{
    // 根據不同的電池電量，使用不同供電方案
    if (B_voltage / counter >= 11.5)
    {
        Battery_100_Percent();
    }
    else if (B_voltage / counter >= 9.0)
    {
        Battery_75_Percent();
    }
    else if (B_voltage / counter >= 6.0)
    {
        Battery_50_Percent();
    }
    // 若電量不足25%，全部切換回到公共電力供電模式
    else if (B_voltage / counter >= 3.0)
    {
        public_elec_mode();
        Serial.println("Battery power < 25%");
        Serial.println("Preserving power for emergency");
        digitalWrite(4, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(10, LOW);
        digitalWrite(13, LOW);
    }
}

// 緊急供電模式
void emergency_mode(double B_voltage, int counter)
{
    // 根據不同電池電量，決定不同供電方案
    if (B_voltage / counter >= 11.5)
    {
        Battery_100_Percent();
    }
    else if (B_voltage / counter >= 9.0)
    {
        Battery_75_Percent();
    }
    else if (B_voltage / counter >= 6.0)
    {
        Battery_50_Percent();
    }
    else if (B_voltage / counter >= 3.0)
    {
        Battery_25_Percent();
    }
}

// 公共電力供電模式，綠能完全不供電
void public_elec_mode()
{
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    Serial.println("public_elec_mode is ON");
}

// 檢查公共電力供電情形，並調整供電方針
void power_check(double B_voltage, int counter)
{
    // 檢查公共電力是否在供電
    double voltage = analogRead(A0) * analogRead(A0) * (-0.000000585) + analogRead(A0) * 0.020823;

    // 若公共電力異常，啟動緊急供電模式
    if (voltage < 2)
    {
        emergency_mode(B_voltage, counter);
    }
    // 若公共電力正常，使用一般供電模式
    else
    {
        normal_mode(B_voltage, counter);
    }
}

// 僅供緊急用電
void Battery_25_Percent()
{
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    Serial.println("Battery is ON");
    Serial.println("Battery power < 25%");
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(10, LOW);
    digitalWrite(13, LOW);
}

// 供給家中重要電器供電
void Battery_50_Percent()
{
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    Serial.println("Battery is ON");
    Serial.println("Battery power 25% ~ 50%");
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(13, LOW);
}

// 供給家中中型電器供電
void Battery_75_Percent()
{
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    Serial.println("Battery is ON");
    Serial.println("Battery power 50% ~ 75%");
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(13, LOW);
}

// 供給家中所有電器供電
void Battery_100_Percent()
{
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    Serial.println("Battery is ON");
    Serial.println("Battery power 75% ~ 100%");
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(13, HIGH);
}