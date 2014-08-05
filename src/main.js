var fs = require('fs')
	,	path = require('path')
	,	XmlStream = require('xml-stream')
	,	filename = path.resolve(__dirname, '../files/eye.xml')
	,	stream = fs.createReadStream(filename)
	,	xml = new XmlStream(stream)
	,	count = 0;

// var haarStruct = {
//   typeId: '',
//   size: {
//     width: 0,
//     height: 0
//   },
//   stages: {
//     count: 0,
//   },
//   stages: {
//     counts: [],
//     thresholds: []
//   },
//   rects: []
// };


function printItem (item) {
  console.log('---- ', JSON.stringify(item, undefined, 2));
}

var haarStruct = {
  typeId: "opencv-haar-classifier",
  nstages: 0,
  stages: [],
  rects: [],
  maxWeakCount: 0,
  cascadeSize: {
    width: 0,
    height: 0
  },
  maxCatCount: 0
};

xml.collect('_');

// xml.on('endElement: cascade > height', function (item) {
//   haarStruct.cascadeSize.height = +item['$text'];
// });

// xml.on('endElement: cascade > width', function (item) {
//   haarStruct.cascadeSize.width = +item['$text'];
// });

xml.on('endElement: stages > _', function (item) {
  var stage = {
    stageThreshold: parseFloat(item.stageThreshold),
    nodes: []
  };

  for (var i in item.weakClassifiers['_']) {
    var internalNodes = item
                          .weakClassifiers['_'][i]
                          .internalNodes.split(' ');
    var node = {
      left_val: '',
      right_val: '',
      threshold: ''
    };

    node.left_val = parseFloat(internalNodes[0]);
    node.right_val = parseFloat(internalNodes[1]);
    node.f = +internalNodes[2];
    node.threshold = parseFloat(internalNodes[3]);

    stage.nodes.push(node);
  }

  haarStruct.nstages++;
  haarStruct.stages.push(stage);

  printItem(stage);
});

xml.on('endElement: _ > rects', function(item) {
	haarStruct.rects.push(item['_']);
});

xml.on('end', function () {
	console.log('\nfinished! ');
  fs.writeFile(filename.replace('.xml', '.json'),
               JSON.stringify(haarStruct, undefined, 2),
   function (err) {
     if (err) throw err;

     console.log('Wrote to: ' + filename.replace('.xml', '.json'));
   });
});
