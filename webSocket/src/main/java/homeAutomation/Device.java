package homeAutomation;

import java.time.LocalTime;

public class Device
{
    public String ip;
    public String mac;
    public String purpose;
    public long timeStamp;
    public boolean active = false;

    Device()
    {
        ip = "";
        mac ="";
        purpose ="";
        timeStamp = LocalTime.now().toSecondOfDay();
    }

    @Override
    public String toString()
    {
        return "[ip=" + ip + ", mac=" + mac + ", purpose=" + purpose  + ", timeStamp=" + timeStamp + ", active=" + active + "]";
    }
}
