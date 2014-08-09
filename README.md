# gulp-cvc-converter

> Converts old type of OpenCV HaarCascade xml data to the new one.

## Process

*cvc-converter* takes a XML of opencv training data (new type), parses it to an internal representation (javascript object) and then pushes to its stdout the tracking.js format of it.

### Example

```javascript
var gulp = require('gulp');
var converterTjs = require('./src/converter-tjs-transform');

gulp.task('default', function () {
  gulp.src('./test/files/eye.xml')
    .pipe(converterTjs())
    .pipe(gulp.dest('./modified-files'));
});
```

```xml
<?xml version="1.0"?>
<opencv_storage>
  <cascade type_id="opencv-cascade-classifier">
    <stageType>BOOST</stageType>
    <featureType>HAAR</featureType>
    <height>20</height>
    <width>20</width>
    <stageParams>
      <maxWeakCount>1</maxWeakCount>
    </stageParams>
    <featureParams>
      <maxCatCount>0</maxCatCount>
    </featureParams>
    <stageNum>1</stageNum>
    <stages>
      <_>
        <maxWeakCount>1</maxWeakCount>
        <stageThreshold>-1.4562760591506958e+00</stageThreshold>
        <weakClassifiers>
          <_>
            <internalNodes>0 -1 0 1.2963959574699402e-01</internalNodes>
            <leafValues>-7.7304208278656006e-01 6.8350148200988770e-01</leafValues>
          </_>
        </weakClassifiers>
      </_>
    </stages>
    <features>
    	<_>
        <rects>
          <_>0 8 20 12 -1.</_>
          <_>0 14 20 6 2.</_>
        </rects>
        <tilted>1</tilted>
      </_>
    </features>
  </cascade>
</opencv_storage>
```

turns into

```json
{
  "nstages": 1,
  "stages": [
    {
      "stageThreshold": -1.4562760591506958,
      "nodes": [
        {
          "left_val": 0,
          "right_val": -1,
          "threshold": 0.12963959574699402,
          "f": 0
        }
      ],
      "nnodes": 1
    }
  ],
  "rects": [
    {
      "data": [
        "0 8 20 12 -1.",
        "0 14 20 6 2."
      ],
      "tilted": 1
    }
  ],
  "maxWeakCount": 0,
  "cascadeSize": {
    "width": 20,
    "height": 20
  },
  "maxCatCount": 0
}
```

which turns into

```json
[20,20,-1.4562760591506958,1,1,2,0,8,20,12,-1,0,14,20,6,2,0.12963959574699402,0,-1]
```
