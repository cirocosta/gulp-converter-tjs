# gulp-converter-tjs [![Build Status](https://travis-ci.org/cirocosta/gulp-converter-tjs.svg?branch=master)](https://travis-ci.org/cirocosta/gulp-converter-tjs)

> Converts new and old type of [OpenCV](https://github.com/Itseez/opencv) HaarCascade XML data to [tracking.js](https://github.com/eduardolundgren/tracking.js)' internal format.

## Process

*converter-tjs* takes a XML of OpenCV training data (new or old type), parses it to an internal representation (JavaScript object) and then pushes to stdout the *tracking.js* representation of it.

### Example

```javascript
var gulp = require('gulp');
var converterTjs = require('gulp-converter-tjs');

gulp.task('default', function () {
  gulp.src('./test/files/haarcascade_frontalface_alt.xml')
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
          "left_val": -0.77304208278656006,
          "right_val": -0.68350148200988770,
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

```javascript
[20,20,-1.4562760591506958,1,1,2,0,8,20,12,-1,0,14,20,6,2,0.12963959574699402, -0.77304208278656006,-0.68350148200988770]

// which is similar to a flattened nested array w/ loops ('[]') like the following:

[width, height,
	[stageThreshold, nodeLength,
		[tilted, rectsLength,
			[rL, rT, rW, rH, rWeigth]
		 nThreshold, nL, nR]]]
```
