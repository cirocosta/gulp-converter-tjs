'use strict';

var fs = require('fs')
  , path = require('path')
  , XmlStream = require('xml-stream');

/**
 * Constructor
 */
function ConverterTJS () {
  if (!(this instanceof ConverterTJS))
    return new ConverterTJS();
}


/**
 * Converts the new type of opencv haarcascade
 * classifiers to an internal representation.
 * @param  {stream}   stream stream of xml
 * @param  {Function} cb     callback function
 *                           to be resolved with
 *                           (err|data), w/ data
 *                           being the result
 *                           structure
 */
ConverterTJS.prototype.convert = function (stream, cb) {
  if (!stream)
    throw new Error('A stream must be passed');

  var f = 0;
  var g = 0;

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

  xml.on('endElement: size', function (item) {
    var sizes = item['$text'].split(' ');

    haarStruct.cascadeSize.width = +sizes[0];
    haarStruct.cascadeSize.height = +sizes[1];
  });

  xml.on('endElement: cascade > height', function (item) {
    haarStruct.cascadeSize.height = +item['$text'];
  });

  xml.on('endElement: cascade > width', function (item) {
    haarStruct.cascadeSize.width = +item['$text'];
  });

  xml.on('endElement: stages > _', function (item) {
    if (!item.trees) {
      // dealing with the new type
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

        g++;

        node.left_val = parseFloat(leafValues[0]);
        node.right_val = parseFloat(leafValues[1]);
        node.f = +internalNodes[2];
        node.threshold = parseFloat(internalNodes[3]);

        stage.nodes.push(node);
      }

      haarStruct.nstages++;
      haarStruct.stages.push(stage);
    } else {
      // dealing with the old type
      var trees = item.trees._;
      var stage = {
        stageThreshold: parseFloat(item.stage_threshold),
        nodes: []
      };

      stage.nnodes = trees.length;

      for (var i in trees) {
        var tree = trees[i]._;
        var node = {
          "left_val": parseFloat(tree[0].left_val),
          "right_val": parseFloat(tree[0].right_val),
          "threshold": parseFloat(tree[0].threshold),
          "f": f++
        };

        g++;
        stage.nodes.push(node);

        haarStruct.rects.push({
          data: tree[0].feature.rects._,
          tilted: +tree[0].feature.tilted
        });
      }

      haarStruct.nstages++;
      haarStruct.stages.push(stage);
    }
  });

  xml.on('endElement: features > _', function(item) {
    haarStruct.rects.push({
      data: item.rects['_'],
      tilted: item.tilted ? 1 : 0
    });

    f++;
  });

  xml.on('error', function (err) {
    cb(err);
  });

  xml.on('end', function () {
    if (g !== f)
      return cb(new Error('Number of rects does not mach number of Nodes'));
    cb(null, haarStruct);
  });
};

/**
 * Converts from the internal structure to
 * tracking.js-ready opencv representation of
 * haarcascade classifiers
 * @param  {Object} orig the internal rep of the
 *                       xml passed to convert
 * @return {[type]}      the tracking.js-ready
 *                           rep
 */
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
