package org.deviceListener;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;
import jakarta.inject.Inject;
import jakarta.websocket.*;

import java.lang.reflect.Type;
import java.net.URI;
import java.util.List;

@ClientEndpoint
public class ClientDeviceListener {

    private DeviceData deviceData;

    private Session session;
    private String uri;

    ClientDeviceListener(String uri, DeviceData  deviceData)
    {
        this.uri = uri;
        this.deviceData = deviceData;
    }

    @OnOpen
    public void onOpen(Session session) {
        this.session = session;
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

    @OnMessage
    public void onMessage(String message) {
        System.out.println("Message from '" + uri + "' :" + message);

        Type deviceListType = new TypeToken<List<Device>>() {}.getType();
        deviceData.setDevices(new Gson().fromJson(message, deviceListType));
    }

    public void send(String message) {
        try {
            if (session == null || !session.isOpen()) {
                connect();
            }

            if (session != null && session.isOpen()) {
                session.getAsyncRemote().sendText(message);
            } else {
                System.err.println("Unable to send message: WebSocket is not connected");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void connect() {
        WebSocketContainer container = ContainerProvider.getWebSocketContainer();
        try {
            container.connectToServer(this, URI.create(this.uri));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
