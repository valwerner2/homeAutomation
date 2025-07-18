package org.deviceListener;

import java.net.DatagramPacket;
import java.net.DatagramSocket;

public class DeviceListenerUdpServer implements Runnable {
    private final int port = 4210;

    public DeviceListenerUdpServer() {}

    @Override
    public void run() {
        try (DatagramSocket socket = new DatagramSocket(port)) {
            byte[] buffer = new byte[1024];
            System.out.println("Listening for UDP packets...");

            while (true) {
                DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
                socket.receive(packet);

                String message = new String(packet.getData(), 0, packet.getLength());
                System.out.println(message);
                DeviceListenerClient.send(message);
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}