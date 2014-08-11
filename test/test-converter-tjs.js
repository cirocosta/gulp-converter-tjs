'use strict';

var assert = require('assert')
  , ConverterTJS = require('../src/converter-tjs')
  , fs = require('fs')
  , filename = require('path').resolve(__dirname, './files/eye.xml');

describe('converter', function() {
  it('should be sane', function() {
    assert(!!ConverterTJS);
  });

  var converter = new ConverterTJS();

  describe('convert', function() {
    it('should convert directly from a stream', function(done) {
      var stream = fs.createReadStream(filename, {encoding: 'utf8'});
      converter.convert(stream, function (err, result) {
        if (err) done(err);

        var expected = fs.readFileSync(filename.replace('.xml', '.json'));

        assert.deepEqual(result, JSON.parse(expected));
        done();
      })
    });
  });

  describe('toTJS', function() {
    it('should convert by passing source and dest', function() {
      var fileRes = fs.readFileSync(filename.replace('.xml', '-tjs.json'));
      var orig = fs.readFileSync(filename.replace('.xml', '.json'));

      var expected = JSON.parse(fileRes);
      var actual = converter.toTJS(JSON.parse(orig));

      assert.deepEqual(actual, expected)
    });
  });
});
