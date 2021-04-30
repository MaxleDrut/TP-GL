```
Algorithm FR5_reliable is
    input: Sensor sensorToCheck
    output: Boolean isReliable
    call: FR5_reliable(Sensor sensorToCheck)
{
    // get a list of all measurements
    function getAllMeasurements() -> Measurement[] allMeasurements

    // removes all the measurements from a measurement list of a given sensor
    function removeAllMeasurementsFromSensor(Measurement[] measurements, Sensor sensor) -> Measurement[] remainingMeasurements

    // returns True if the given sensor is considered reliable, False otherwise
    function FR5_reliable(Sensor sensorToCheck) -> Boolean isReliable
        var Measurement[] measurements := getAllMeasurements()
        measurements := removeAllMeasurementsFromSensor(measurements, sensorToCheck)

        var Float relativeSum := 0.0
        var Integer nbOfMeasurementsForSensorToCheck := 0

        // for every measurement of the sensor, check if it is close to the expected one or not by adding to relative sum
        for each measurement in sensorToCheck.getMeasurements()
            var Map<Attribute, Float> expectedValues := FR8_qualityAttributes(ALWAYS, measurement.getSensor().position)
            var Float expectedValue := expectedValues[measurement.attribute]
            var Float relativeDiff := abs(expectedValue - measurement.value) / expectedValue // compute the relative difference

            relativeSum := relativeSum + relativeDiff
            nbOfMeasurementsForSensorToCheck := nbOfMeasurementsForSensorToCheck + 1
        
        var Float averageRelative := relativeSum / nbOfMeasurementsForSensorToCheck
        
        // if the relative deviation is > 50%, consider the sensor not to be reliable
        var Boolean isReliable := False
        if averageRelative > 0.5
            isReliable := False

        return isReliable
}
```