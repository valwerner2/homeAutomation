package homeAutomation;

import jakarta.enterprise.context.ApplicationScoped;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

@ApplicationScoped
public class DeviceReachabilityData
{
    private final Map<String, Device> devices = new ConcurrentHashMap<>();

    public Map<String, Device> getDevices() {
        return devices;
    }
}
