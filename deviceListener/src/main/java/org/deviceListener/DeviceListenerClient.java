package org.deviceListener;

import jakarta.websocket.*;
import java.net.URI;

@ClientEndpoint
public class DeviceListenerClient {

    private static Session session;

    @OnOpen
    public void onOpen(Session session) {
        DeviceListenerClient.session = session;
        System.out.println("Connected to WebSocket server");
    }

    @OnClose
    public void onClose(Session session, CloseReason reason) {
        System.out.println("Disconnected: " + reason);
    }

    @OnError
    public void onError(Session session, Throwable t) {
        System.err.println("WebSocket error: " + t.getMessage());
    }

    public static void send(String message) {
        if (session != null && session.isOpen()) {
            session.getAsyncRemote().sendText(message);
        } else {
            System.err.println("WebSocket not connected. Message dropped.");
        }
    }

    public static void connect(String uri) {
        WebSocketContainer container = ContainerProvider.getWebSocketContainer();
        try {
            container.connectToServer(DeviceListenerClient.class, URI.create(uri));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
