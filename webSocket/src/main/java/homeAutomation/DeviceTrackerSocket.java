package homeAutomation;

import com.google.gson.Gson;

import jakarta.annotation.PostConstruct;
import jakarta.enterprise.context.ApplicationScoped;
import jakarta.websocket.OnClose;
import jakarta.websocket.OnError;
import jakarta.websocket.OnMessage;
import jakarta.websocket.OnOpen;
import jakarta.websocket.Session;
import jakarta.websocket.server.ServerEndpoint;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.CopyOnWriteArrayList;
import java.util.concurrent.atomic.AtomicBoolean;


@ServerEndpoint("/homeAutomation/ws/deviceTracker")
@ApplicationScoped
public class DeviceTrackerSocket {

    List<Session> sessions = new CopyOnWriteArrayList<>();
    Map<String, Device> devices = new ConcurrentHashMap<>();
    Gson gson = new Gson();
    DevicesBroadcaster broadcaster = new DevicesBroadcaster(sessions, devices);

    @PostConstruct
    void init()
    {
        new Thread(new DeviceTimeTracker(devices, broadcaster)).start();
    }

    @OnOpen
    public void onOpen(Session session)
    {
        System.out.println("onOpen>");
        session.getAsyncRemote().sendText(gson.toJson(new ArrayList<>(devices.values())));
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
        boolean isNewDevice = !devices.containsKey(receivedDevice.mac);

        //keep old active state
        if(!isNewDevice) { receivedDevice.active = devices.get(receivedDevice.mac).active; }

        devices.put(receivedDevice.mac, receivedDevice);

        //tell everyone about the new device
        if(isNewDevice) { broadcaster.broadcastDevices(); }
    }
}
