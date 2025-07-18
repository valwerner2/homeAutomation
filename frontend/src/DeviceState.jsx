import {useEffect, useState} from "react";

function DeviceState({device, name}) {
    const [stateMsg, setStateMsg] = useState("")

    useEffect(() => {
        if(device)
        {
            if(device.active)
            {
                setStateMsg(name + " Online @ " + device.ip)
            }
            else
            {
                setStateMsg(name + " Offline (last seen @ " + device.ip + ")")
            }
        }
        else
        {
            setStateMsg(name + " not found");
        }

    }, [device]);

    return (
        <div>
            {stateMsg}
        </div>
    )
}

export default DeviceState;