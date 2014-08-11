'use strict';

var fs = require('fs')
  , path = require('path')
  , XmlStream = require('xml-stream');


function ConverterTJS () {
  if (!(this instanceof ConverterTJS))
    return new ConverterTJS();
}

ConverterTJS.prototype.convert = function (stream, cb) {
  if (!stream)
    throw new Error('A stream must be passed');

  var xml = new XmlStream(stream);
  var haarStruct = {
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

  xml.on('endElement: cascade > height', function (item) {
    haarStruct.cascadeSize.height = +item['$text'];
  });

  xml.on('endElement: cascade > width', function (item) {
    haarStruct.cascadeSize.width = +item['$text'];
  });

  xml.on('endElement: stages > _', function (item) {
    var stage = {
      stageThreshold: parseFloat(item.stageThreshold),
      nodes: []
    };

    stage.nnodes = item.weakClassifiers['_'].length;

    for (var i = 0 ; i < stage.nnodes; i++) {
      var internalNodes = item
                            .weakClassifiers['_'][i]
                            .internalNodes.split(' ');
      var leafValues = item
                          .weakClassifiers['_'][i]
                          .leafValues.split(' ');
      var node = {
        left_val: '',
        right_val: '',
        threshold: ''
      };

      node.left_val = parseFloat(leafValues[0]);
      node.right_val = parseFloat(leafValues[1]);
      node.f = +internalNodes[2];
      node.threshold = parseFloat(internalNodes[3]);

      stage.nodes.push(node);
    }

    haarStruct.nstages++;
    haarStruct.stages.push(stage);
  });

  xml.on('endElement: features > _', function(item) {
    haarStruct.rects.push({
      data: item.rects['_'],
      tilted: item.tilted ? 1 : 0
    });
  });

  xml.on('error', function (err) {
    cb(err);
  });

  xml.on('end', function () {
    cb(null, haarStruct);
  });
};


ConverterTJS.prototype.toTJS = function (orig) {
  var results = [];
  var f = 0;

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

  return results;
};

module.exports = ConverterTJS;
