var fs = require('fs')
  , path = require('path')
  , orig = require('../files/eye.json')
  , results = []
  , f = 0;

// width and height

results.push(orig.cascadeSize.width);
results.push(orig.cascadeSize.height);

// iterate through stages

for (var i = 0; i < orig.nstages;) {
  // stageThreshold, nodeLength
  var stage = orig.stages[i++];

  results.push(stage.stageThreshold);
  results.push(stage.nodes.length);

  // iterate through nodes
  for (var j = 0; j < stage.nnodes;) {
    // tilted, rectsLength
    var node = stage.nodes[j++];
    var rect = orig.rects[f++];

    results.push(rect.tilted);
    results.push(rect.data.length);

    // iterate through rects
    for (var k = 0, N = rect.data.length; k < N;) {
      // rectLeft, rectTop, rectWidth, rectHeight, rectWeight
      var R = rect.data[k++].split(' ');
      for (var l = 0, M = R.length; l < M; l++)
        results.push(+R[l]);
    }

    results.push(node.threshold);
    results.push(node.left_val);
    results.push(node.right_val);
  }
}

var filename = path.resolve(__dirname, './eye-tracking.json');
fs.writeFile(filename, JSON.stringify(results), function (err) {
   if (err) throw err;

   console.log('Wrote to: ' + filename);
 });
