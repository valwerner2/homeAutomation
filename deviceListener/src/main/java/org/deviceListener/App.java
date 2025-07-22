package org.deviceListener;


public class App 
{
    public static void main( String[] args )
    {
        DeviceData deviceData = new DeviceData();

        String deviceSocketUri = "ws://127.0.0.1:8080/homeAutomation/ws/deviceTracker";
        ClientDeviceListener deviceSocket = new ClientDeviceListener(deviceSocketUri, deviceData);
        deviceSocket.connect();
        new Thread(new UdpServerDeviceListener(deviceSocket)).start();

        String automationSockerUri = "ws://127.0.0.1:8080/homeAutomation/ws/automationService";
        ClientAutomation automationSocket = new ClientAutomation(automationSockerUri, deviceData);
        automationSocket.connect();

    }
}
