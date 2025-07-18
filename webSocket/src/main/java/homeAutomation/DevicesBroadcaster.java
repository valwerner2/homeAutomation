package homeAutomation;

import jakarta.websocket.Session;

import com.google.gson.Gson;


import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.atomic.AtomicBoolean;

public class DevicesBroadcaster
{
    List<Session> sessions;
    Map<String, Device> devices;
    Gson gson = new Gson();

    DevicesBroadcaster(List<Session> sessions, Map<String, Device> devices)
    {
        this.sessions = sessions;
        this.devices = devices;
    }
    public void broadcastDevices()
    {
        System.out.println("\n----- Broadcasting -----\n");
        broadcast(gson.toJson(new ArrayList<>(devices.values())));
    }
    public void broadcast(String message)
    {
        sessions.forEach(session -> session.getAsyncRemote().sendText(message));
    }
}
