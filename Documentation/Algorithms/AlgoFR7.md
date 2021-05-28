```
Algorithm FR7_sensorComparison is
    inputs: Sensor sensorToCompare, timestamp t1, timestamp t2
    output: Map<Sensor,double> proximity
    Pre-condition: sensorToCompare has measurements during the specified period
    call: FR7_sensorComparison(Sensor sensorToCompare, timestamp t1, timestamp t2)
{
    function getAllSensors() -> Sensor[] allSensors

    // Calculates the average value of a targetted attribute of a sensor between t1 and t2
    function FR7_averageValue(Sensor sensor, Attribute targetAttribute, timestamp t1, timestamp t2)
        var Double sum := 0
        var Integer checkedMeasurement :=0
        for each measurement in sensor.measurements
            if measurement.attribute.identifier = targetAttribute.identifier and measurement.timestamp > t1 and measurement.timestamp < t2
                sum += measurement.value
                checkedMeasurement+=1

        return sum/checkedMeasurement
    

    //Calculates the proximity of all sensors compared to the targetted sensor: Calculates the relative gap between the average target value and the other sensors. Returns a map of all sensors with their target's proximity
    function FR7_sensorComparison(Sensor sensorToCompare, timestamp t1, timestamp t2) {

        var Map<Sensor, double> proximity

        var Double refValues[4]; //Stores the average value of the target sensor
        var Integer i:=0
        for each attribute //NO2, O3, PM10...
            refValues[i] := FR7_averageValue(sensorToCompare,attribute,t1,t2)
            i+=1
        
        for each sensor in getAllSensors()
            if sensor!=sensorToCompare
                var Double relative_gap := 0
                var Integer i := 0
                for each attribute
                    var Double average := FR7_averageValue(sensor,attribute,t1,t2)
                    relative_gap += absolute(average-refValues[i])/refValues[i]
                    i+=1

                relative_gap := relative_gap/i

                proximity[sensor] = 1/(relative_gap+1)
        
        return proximity
    }

}
```
