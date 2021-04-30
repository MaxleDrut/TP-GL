```
algorithm FR8_quality is
    inputs: Period timePeriod, Position askedPosition
    output: ATMOData predictedATMOScore
    call: FR8_quality(Period timePeriod, Position askedPosition)
{
    // returns True if the timestamp is inside the period, False otherwise.
    function isGivenTimeInsideTimePeriod(Pediod period, Time timestamp) -> Boolean isInside 
        if period.start <= timestamp and period.end >= timestamp
            return true
        else
            return false
    
    // returns the distance between 2 positions
    function distanceBetweenPositions(Position a, Position b) -> Float distance

    // get a random Sensor, the fastest to get actually
    function getASensor() -> Sensor sensor

    // convert 
    function convertValuesAttributesToATMOCoefficient(Map<Attribute, Float> values) -> ATMOData predictedATMOScore

    // get a list of all measurements
    function getAllMeasurements() -> Measurement[] allMeasurements
    
    // returns predicted values for ATMO attributes for a given position and a considered period of time for the data
    function FR8_qualityAttributes(Period timePeriod, Position askedPosition) -> Map<Attribute, Float> attributesPredictedValues
        var Attribute[] attributes := getAllAttributes() // an array of all data types (Attibutes)
        var Measurement[] allMeasurements := getAllMeasurements()

        var Map<Attribute, Float> numeratorSums := {
            attributes.O3: 0.0,
            attributes.NO3: 0.0,
            attributes.SO2: 0.0,
            attributes.PM10: 0.0
        }
        var Map<Attribute, Float> denominatorSums := {
            attributes.O3: 0.0,
            attributes.NO3: 0.0,
            attributes.SO2: 0.0,
            attributes.PM10: 0.0
        }

        var Sensor referentiel := getASensor()

        for each measurement in allMeasurements
            if measurement.getSensor().reliable and isGivenTimeInsideTimePeriod(timePeriod, measurement.timestamp)
                var Float coefficient := distanceBetweenPositions(referentiel.position, measurement.getSensor().position)
                numeratorSums[measurement.attribute] := numeratorSums[measurement.attribute] + (coefficient * measurement.value)
                denominatorSums[measurement.attribute] := denominatorSums[measurement.attribute] + coefficient
        
        var Map<Attribute, Float> attributesPredictedValues := {
            attributes.O3: 0.0,
            attributes.NO3: 0.0,
            attributes.SO2: 0.0,
            attributes.PM10: 0.0
        }
        attributesPredictedValues := numeratorSum/denominatorSums
        
        return attributesPredictedValues
    
    // returns a ATMO coefficient for a given position and a considered period of time for the data
    function FR8_quality(Period timePeriod, Position askedPosition) -> ATMOData predictedATMOScore
        var Map<Attribute, Float> results := FR8_qualityAttributes
        return convertValuesAttributesToATMOCoefficient(results)

}   
```