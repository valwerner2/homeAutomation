package org.deviceListener;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;
import jakarta.annotation.PostConstruct;
import jakarta.websocket.*;

import java.lang.reflect.Type;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

@ClientEndpoint
public class ClientAutomation
{
    private DeviceData deviceData;
    private Session session;
    private String uri;
    private List<AutomationTask> automations = new CopyOnWriteArrayList<>();

    ClientAutomation(String uri, DeviceData  deviceData)
    {
        this.uri = uri;
        this.deviceData = deviceData;

        AutomationRunner runner = new AutomationRunner(deviceData, automations);
        ScheduledExecutorService scheduler = Executors.newSingleThreadScheduledExecutor();

        // Run every 5 seconds
        scheduler.scheduleAtFixedRate(runner, 0, 5, TimeUnit.SECONDS);
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
        Type deviceListType = new TypeToken<List<AutomationTask>>() {}.getType();
        automations.clear();
        List<AutomationTask> temp = new Gson().fromJson(message, deviceListType);
        for(AutomationTask task : temp)
        {
            automations.add(task);
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
