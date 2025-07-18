package homeAutomation;

import java.time.LocalTime;
import java.util.Map;
import java.util.concurrent.Callable;
import java.util.concurrent.atomic.AtomicBoolean;

import static java.lang.Thread.sleep;

public class DeviceTimeTracker implements Runnable
{
    final long maxOfflineSeconds = 10;
    final long checkingDelay = 2;
    DevicesBroadcaster broadcaster;
    Map<String, Device> devices;

    DeviceTimeTracker(Map<String, Device> devices, DevicesBroadcaster broadcaster)
    {
        this.devices =  devices;
        this.broadcaster = broadcaster;
    }

    public void checkDevices()
    {
        System.out.println("----- Checking devices -----");
        boolean changed = false;
        for (Device currentDevice : devices.values())
        {
            long secondsOffline = LocalTime.now().toSecondOfDay() - currentDevice.timeStamp;

            if(secondsOffline <= maxOfflineSeconds != currentDevice.active)
            {
                changed = true;
            }
            currentDevice.active = secondsOffline <= maxOfflineSeconds;
            System.out.println(currentDevice);
        }
        System.out.println("----------------------------\n");

        if(changed)
        {
            broadcaster.broadcastDevices();
        }
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
