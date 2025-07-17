package org.deviceListener;

import java.net.DatagramPacket;
import java.net.DatagramSocket;

public class DeviceListener implements Runnable {
    private final int port = 4210;

    public DeviceListener() {}

    @Override
    public void run() {
        try (DatagramSocket socket = new DatagramSocket(port)) {
            byte[] buffer = new byte[1024];
            System.out.println("Listening for UDP packets...");

            while (true) {
                DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
                socket.receive(packet);

                String message = new String(packet.getData(), 0, packet.getLength());
                System.out.println("UDP received: " + message);

            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}