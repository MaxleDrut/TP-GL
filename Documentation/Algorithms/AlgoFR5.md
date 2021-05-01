```
Algorithm FR5_malfunctioningAnalysis is
    input: Sensor sensorToCheck
    output: Double averageRelativeGap
    call: FR5_malfunctioningAnalysis(Sensor sensorToCheck)
{
    // get a list of all measurements
    function getAllMeasurements() -> Measurement[] allMeasurements

    // removes all the measurements from a measurement list of a given sensor
    function removeAllMeasurementsFromSensor(Measurement[] measurements, Sensor sensor) -> Measurement[] remainingMeasurements

    // returns True if the given sensor is considered reliable, False otherwise
    function FR5_malfunctioningAnalysis(Sensor sensorToCheck) -> Boolean isReliable
        var Measurement[] measurements := getAllMeasurements()
        measurements := removeAllMeasurementsFromSensor(measurements, sensorToCheck)

        var Double relativeSum := 0.0
        var Integer nbOfMeasurementsForSensorToCheck := 0

        // for every measurement of the sensor, check if it is close to the expected one or not by adding to relative sum
        for each measurement in sensorToCheck.getMeasurements()
            var Map<Attribute, Double> expectedValues := FR8_qualityAttributes(ALWAYS, measurement.getSensor().position)
            var Double expectedValue := expectedValues[measurement.attribute]
            var Double relativeDiff := abs(expectedValue - measurement.value) / expectedValue // compute the relative difference

            relativeSum := relativeSum + relativeDiff
            nbOfMeasurementsForSensorToCheck := nbOfMeasurementsForSensorToCheck + 1
        
        var Double averageRelativeGap := relativeSum / nbOfMeasurementsForSensorToCheck
        
        return averageRelativeGap
}
```