package org.deviceListener;


public class App 
{
    public static void main( String[] args )
    {
        String wsUri = "ws://127.0.0.1:8080/homeAutomation/ws/deviceTracker";

        DeviceListenerClient.connect(wsUri);
        new Thread(new DeviceListenerUdpServer()).start();
    }
}
