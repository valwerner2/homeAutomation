package homeAutomation;

import java.time.LocalTime;
import java.util.Map;

import static java.lang.Thread.sleep;

public class DeviceTimeTracker implements Runnable
{
    final long maxOfflineSeconds = 10;
    final long checkingDelay = 2;
    Map<String, Device> devices;

    DeviceTimeTracker(Map<String, Device> devices)
    {
        this.devices =  devices;
    }

    public void checkDevices()
    {
        System.out.println("Checking devices");
        for (Device currentDevice : devices.values())
        {
            long secondsOffline = LocalTime.now().toSecondOfDay() - currentDevice.timeStamp;
            System.out.println("offline for: " + secondsOffline);
            currentDevice.active = secondsOffline <= maxOfflineSeconds;
            System.out.println(currentDevice);
        }
        System.out.println("-------------------");
    }
    @Override
    public void run()
    {
        while (true)
        {
            try {
                sleep(checkingDelay * 1000l);
                checkDevices();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

        }
    }
}
