package org.deviceListener;

import jakarta.enterprise.context.ApplicationScoped;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

@ApplicationScoped
public class DeviceData
{
    private final Map<String, Device> devices = new ConcurrentHashMap<>();

    public Map<String, Device> getDevices()
    {
        return devices;
    }

    public void setDevices(List<Device> updatedDevices)
    {
        for (Device currentDevice : updatedDevices)
        {
            devices.put(currentDevice.mac,  currentDevice);
        }
    }
}
