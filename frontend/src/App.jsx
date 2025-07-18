import './App.css'
import PlantServer from "./PlantServer.jsx";
import {useEffect, useState} from "react";

function App() {

  const deviceState = useState();
  const [devices, setDevices] = deviceState;

  useEffect(() => {
    const ws = new WebSocket("ws://127.0.0.1:8080/homeAutomation/ws/deviceTracker");

    ws.onopen = () => {
      console.log("connected");
    }

    ws.onmessage = (event) => {
      setDevices(JSON.parse(event.data));
      console.log("Update:", JSON.parse(event.data));
    };
  }, [])

  return (
    <div>
    <PlantServer devices={devices}/>
    </div>
  )
}

export default App
