import { useState } from "react";
import GrowLight from "./GrowLight.jsx";

function PlantServer() {
    const ip = "192.168.2.120";


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
            <GrowLight brightnessSate={brightnessSate} get={get} index={1}/>
        </div>
    )
}

export default PlantServer