'use strict';

var assert = require('assert')
  , fs = require('fs')
  , gutil = require('gulp-util')
  , File = require('vinyl')
  , converterTjs = require('../src/converter-tjs-transform')
  , path = require('path').resolve(__dirname, './files');

describe('converterTransform', function() {
  it('should be sane', function() {
    assert(!!converterTjs);
  });

  var converter;

  beforeEach(function () {
    converter = converterTjs();
  });

  it('should not deal with gulp streams', function(done) {
    var stream = fs.createReadStream(path + '/eye.xml');
    var file = new File({contents: stream});

    assert.throws(function () {
      converter.write(file);
    }, 'Streams are not allowed');

    done();
  });

  it('should deal with gulp buffers', function(done) {
      var xml = fs.readFileSync(path + '/eye.xml');
      var file = new File({contents: new Buffer(xml)});

      converter.write(file);
      converter.end();

      converter.once('data', function (f) {
        var actual = JSON.parse(f.contents.toString());
        var expected = JSON.parse(
          fs.readFileSync(path + '/eye-tjs.json'));

        assert.deepEqual(actual, expected);
        done();
      });
    });
});
