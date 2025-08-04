package homeAutomation;

import com.google.gson.Gson;

import io.quarkus.scheduler.Scheduled;
import jakarta.annotation.PostConstruct;
import jakarta.enterprise.context.ApplicationScoped;
import jakarta.inject.Inject;
import jakarta.websocket.OnClose;
import jakarta.websocket.OnError;
import jakarta.websocket.OnMessage;
import jakarta.websocket.OnOpen;
import jakarta.websocket.Session;
import jakarta.websocket.server.ServerEndpoint;

import java.time.LocalTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.concurrent.CopyOnWriteArrayList;

@ServerEndpoint("/homeAutomation/ws/deviceTracker")
@ApplicationScoped
public class EndpointDeviceTracker {

    List<Session> sessions = new CopyOnWriteArrayList<>();
    final long maxOfflineSeconds = 10;
    Gson gson = new Gson();

    @Inject
    DeviceReachabilityData deviceStorage;

    @PostConstruct
    void init() {}

    @OnOpen
    public void onOpen(Session session)
    {
        System.out.println("onOpen>");
        session.getAsyncRemote().sendText(gson.toJson(new ArrayList<>(deviceStorage.getDevices().values())));
        sessions.add(session);
    }

    @OnClose
    public void onClose(Session session)
    {
        System.out.println("onClose>");
        sessions.remove(session);
    }

    @OnError
    public void onError(Session session, Throwable throwable)
    {
        System.out.println("onError>");
        sessions.remove(session);
    }

    @OnMessage
    public void onMessage(String message)
    {
        Device receivedDevice = gson.fromJson(message, Device.class);
        boolean isNewDevice = !deviceStorage.getDevices().containsKey(receivedDevice.mac);

        //keep old active state
        if(!isNewDevice) { receivedDevice.active = deviceStorage.getDevices().get(receivedDevice.mac).active; }

        // check for changed name
        if(!isNewDevice) {isNewDevice = !Objects.equals(deviceStorage.getDevices().get(receivedDevice.mac).name, receivedDevice.name);}

            deviceStorage.getDevices().put(receivedDevice.mac, receivedDevice);

        //tell everyone about the new device
        if(isNewDevice) { broadcastDevices(); }
    }

    @Scheduled(every = "2s")
    public void checkDevices()
    {
        System.out.println("----- Checking devices -----");
        boolean changed = false;
        for (Device currentDevice : deviceStorage.getDevices().values())
        {
            int timeNow = LocalTime.now().toSecondOfDay();

            boolean isOnline = (currentDevice.timeStamp <= timeNow) && (timeNow - currentDevice.timeStamp <= maxOfflineSeconds);

            if(isOnline != currentDevice.active)
            {
                changed = true;
            }
            currentDevice.active = isOnline;
            System.out.println(currentDevice);
        }
        System.out.println("----------------------------\n");

        if(changed)
        {
            broadcastDevices();
        }
    }

    public void broadcastDevices()
    {
        System.out.println("\n----- Broadcasting -----\n");
        broadcast(gson.toJson(new ArrayList<>(deviceStorage.getDevices().values())));
    }

    public void broadcast(String message)
    {
        sessions.forEach(session -> session.getAsyncRemote().sendText(message));
    }
}
