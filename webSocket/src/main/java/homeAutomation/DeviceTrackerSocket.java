package homeAutomation;

import com.google.gson.Gson;

import jakarta.enterprise.context.ApplicationScoped;
import jakarta.websocket.OnClose;
import jakarta.websocket.OnError;
import jakarta.websocket.OnMessage;
import jakarta.websocket.OnOpen;
import jakarta.websocket.Session;
import jakarta.websocket.server.ServerEndpoint;

import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.CopyOnWriteArrayList;

import static java.util.Objects.requireNonNull;

@ServerEndpoint("/homeAutomation/ws/deviceTracker")
@ApplicationScoped
public class DeviceTrackerSocket {

    List<Session> sessions = new CopyOnWriteArrayList<>();
    Map<String, Device> devices = new ConcurrentHashMap<>();
    Gson gson = new Gson();
    Thread threadTimeTracker = new Thread(new DeviceTimeTracker(devices));
    boolean threadTimeTrackerStarted = false;

    @OnOpen
    public void onOpen(Session session)
    {
        System.out.println("onOpen>");
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
        throwable.printStackTrace();
        sessions.remove(session);
    }

    @OnMessage
    public void onMessage(String message)
    {
        if(!threadTimeTrackerStarted)
        {
            threadTimeTrackerStarted = true;
            threadTimeTracker.start();
        }

        Device newDevice = gson.fromJson(message, Device.class);

        devices.put(newDevice.mac, newDevice);
        new DeviceTimeTracker(devices).checkDevices();
    }
}
