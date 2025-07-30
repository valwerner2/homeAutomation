package homeAutomation;

import com.google.gson.Gson;
import jakarta.annotation.PostConstruct;
import jakarta.enterprise.context.ApplicationScoped;
import jakarta.inject.Inject;
import jakarta.websocket.*;
import jakarta.websocket.server.ServerEndpoint;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.CopyOnWriteArrayList;

@ServerEndpoint("/homeAutomation/ws/automationService")
@ApplicationScoped
public class EndpointAutomationService
{
    private final Map<String, AutomationInfo> automations = new ConcurrentHashMap<>();

    private final List<Session> sessions = new CopyOnWriteArrayList<>();
    Gson gson = new Gson();

    @PostConstruct
    void init() {}

    @OnOpen
    public void onOpen(Session session)
    {
        sessions.add(session);
        session.getAsyncRemote().sendText(gson.toJson(new ArrayList<>(automations.values())));
    }

    @OnClose
    public void onClose(Session session)
    {
        sessions.remove(session);
    }

    @OnError
    public void onError(Session session, Throwable throwable)
    {
        sessions.remove(session);
    }

    @OnMessage
    public void onMessage(String message)
    {
        AutomationInfo automationInfo = gson.fromJson(message, AutomationInfo.class);

        String key = automationInfo.type + automationInfo.macSensor + automationInfo.sensorEndpoint + automationInfo.macSlave + automationInfo.slaveEndpoint;
        if(automationInfo.command.equals("delete"))
        {
            automations.remove(key);
        }
        else
        {
            automations.put(key,  automationInfo);
        }

        broadcastAutomations();
    }

    public void broadcastAutomations()
    {
        broadcast(gson.toJson(new ArrayList<>(automations.values())));
    }
    public void broadcast(String message)
    {
        sessions.forEach(session -> session.getAsyncRemote().sendText(message));
    }
}
