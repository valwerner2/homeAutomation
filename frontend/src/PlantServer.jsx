import {useEffect, useState} from "react";
import GrowLight from "./GrowLight.jsx";
import DeviceState from "./DeviceState.jsx";

function PlantServer({devices}) {
    const ip = "192.168.2.120";
    const [plantServer, setPlantServer] = useState(null);

    useEffect(() => {
        console.log("Plant Server");
        if(devices)
        {
            setPlantServer(devices.find(device => device.purpose === "plantServer"));
        }
    }, [devices]);


    const get = async (url) => {
        try {
            const res = await fetch(`http://${ip}/${url}`);
            if (res.ok) {
                console.log("Brightness set successfully");
            } else {
                console.error("Failed to set brightness:", res.status);
            }
        } catch (err) {
            console.error("Error setting brightness:", err);
        }
    };
    const brightnessSate = useState(10);

    return (
        <div>
            <DeviceState device={plantServer} name={"PlantServer"} />
            <GrowLight brightnessSate={brightnessSate} get={get} index={1}/>
        </div>
    )
}

export default PlantServer