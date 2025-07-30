package org.deviceListener;

import com.google.gson.Gson;

import java.io.IOException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.HashMap;
import java.util.Map;

public class AutomationTask
{
    String command;
    String type;
    String macSensor;
    String macSlave;
    String sensorEndpoint;
    String slaveEndpoint;
    Map<String, String> properties;

    class AthData
    {
        String temperature;
        String humidity;
    }

    private String sendHttpRequest(String cmd, String url) {
        HttpClient client = HttpClient.newHttpClient();
        HttpRequest request = null;

        if ("get".equalsIgnoreCase(cmd)) {
            request = HttpRequest.newBuilder()
                    .uri(URI.create(url))
                    .GET()
                    .build();
        }

        if (request != null) {
            try {
                HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());
                return response.body();
            } catch (IOException | InterruptedException e) {
                System.err.println("HTTP request failed: " + e.getMessage());
            }
        }

        return "";
    }

    void execute(DeviceData deviceData, Map<String, Map<String, String>> automationData)
    {
        switch (type)
        {
            case "ath20":
                executeAht20(deviceData, automationData);
                break;
            default:
                break;
        }
    }
    void executeAht20(DeviceData deviceData, Map<String, Map<String, String>> automationData)
    {
        Device sensor = deviceData.getDevices().get(macSensor);
        Device slave = deviceData.getDevices().get(macSlave);

        String key = type + macSensor + sensorEndpoint + macSlave + slaveEndpoint;

        boolean newAutomation = !automationData.containsKey(key);

        if(newAutomation)
        {
            automationData.put(key, new HashMap<>());
            Map<String, String> tempData = automationData.get(key);
            tempData.put("lastTemperature", Double.toString(0.0));
            tempData.put("lastHumidity", Double.toString(0.0));
        }

        Map<String, String> data = automationData.get(key);

        System.out.println("sensor? " + sensor.active);
        if(sensor.active)
        {
            AthData athData = new Gson().fromJson(sendHttpRequest("get",  "http://" + sensor.ip + sensorEndpoint), AthData.class);
            data.put("lastTemperature", athData.temperature);
            data.put("lastHumidity", athData.humidity);
        }

        System.out.println("lastTemperature: " + data.get("lastTemperature") + "\nlastHumidity: " + data.get("lastHumidity"));
    }

}
