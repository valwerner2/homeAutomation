import { useEffect, useRef } from 'react';

import Slider from "./Silder.jsx";

function GrowLight({brightnessSate, get, index}) {
    const didMount = useRef(false);
    const [brightness, setBrightness] = brightnessSate;
    const DEBOUNCE_DELAY_MS = 300;

    useEffect(() => {
        if (!didMount.current){
            didMount.current = true;
            return;
        }

        let timeoutId;

        timeoutId = setTimeout(() => {
            get(`growLight${index}Brightness?value=${brightness}`);
        }, DEBOUNCE_DELAY_MS);

        return () => {
            clearTimeout(timeoutId);
        };

    }, [brightness]);

    return (
        <div>
            <Slider label={"GrowLight"} sliderState={brightnessSate} />
        </div>
    )
}
export default GrowLight;