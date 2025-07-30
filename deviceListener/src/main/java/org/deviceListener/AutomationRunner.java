package org.deviceListener;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class AutomationRunner implements Runnable
{
    List<AutomationTask> automations;
    DeviceData deviceData;
    Map<String, Map<String, String>> automationData;

    AutomationRunner(DeviceData  deviceData, List<AutomationTask> automations)
    {
        this.automations = automations;
        this.deviceData = deviceData;
        this.automationData = new HashMap<>();
    }

    @Override
    public void run()
    {
        for (AutomationTask task : automations) {
            try {
                task.execute(deviceData, automationData);
            } catch (Exception e) {
                System.err.println("[AutomationRunner] Error in task '" + task.type + "': " + e.getMessage() + "\n");
                e.printStackTrace();
            }
        }
    }
}
