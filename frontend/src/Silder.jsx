function Slider({label, sliderState}) {
    const [value, setValue] = sliderState;

    const handleChange = (e) => {
        setValue(Number(e.target.value));
    };

    return (
        <div>
            <label>{label}: {value}%</label>
            <input
                type="range"
                min="0"
                max="100"
                value={value}
                onChange={handleChange}
            />
        </div>
    )
}
export default Slider;