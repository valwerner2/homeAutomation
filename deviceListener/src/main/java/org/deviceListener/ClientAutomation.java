package org.deviceListener;

import jakarta.websocket.*;

import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;

@ClientEndpoint
public class ClientAutomation
{
    private DeviceData deviceData;
    private Session session;
    private String uri;

    ClientAutomation(String uri, DeviceData  deviceData)
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
    public void onMessage(String message)
    {
        System.out.println("Message from '" + uri + "' :" + message);
    }

    private void sendHttpRequest(String url) {
        HttpClient client = HttpClient.newHttpClient();
        HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create(url))
                .GET()
                .build();

        client.sendAsync(request, HttpResponse.BodyHandlers.ofString())
                .thenAccept(response -> {
                    System.out.println("HTTP response status: " + response.statusCode());
                    System.out.println("HTTP response body: " + response.body());
                })
                .exceptionally(e -> {
                    System.err.println("HTTP request failed: " + e.getMessage());
                    return null;
                });
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
