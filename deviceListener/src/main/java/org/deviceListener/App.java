package org.deviceListener;


public class App 
{
    public static void main( String[] args )
    {
        new Thread(new DeviceListener()).start();
    }
}
