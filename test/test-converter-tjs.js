'use strict';

var fs = require('fs')
  , path = require('path')
  , assert = require('assert')
  , ConverterTJS = require('../src/converter-tjs')
  , Readable = require('stream').Readable || require('readable-stream');


function createStream (data) {
  var rs = new Readable({ objectMode: true });
  rs.push(data);
  rs.push(null);

  return rs;
}

describe('converter', function() {
  it('should be sane', function() {
    assert(!!ConverterTJS);
  });

  var converter = new ConverterTJS();
  var filesPath = path.resolve(__dirname, './files');

  describe('convert', function() {
    it('should convert directly from a stream', function(done) {
      var stream = fs.createReadStream(filesPath + '/eye.xml',
                                       {encoding: 'utf8'});

      converter.convert(stream, function (err, result) {
        if (err) done(err);

        var expected = fs.readFileSync(filesPath + '/eye.json');

        assert.deepEqual(result, JSON.parse(expected));
        done();
      })
    });

    it('should convert from a fake stream', function (done) {
      var fileContent = fs.readFileSync(filesPath + '/eye.xml',
                                        {enconding: 'utf8'});
      var stream = createStream(fileContent);

      converter.convert(stream, function (err, result) {
        if (err) done(err);

        var expected = fs.readFileSync(filesPath + '/eye.json');

        assert.deepEqual(result, JSON.parse(expected));
        done();
      });
    });

    it('should throw if malformed haar cascade', function(done) {
      var stream = fs.createReadStream(filesPath + '/eye-malformed.xml',
                                       {encoding: 'utf8'});

      converter.convert(stream, function (err, result) {
        if (err)
          (assert(err), done());
        else
          done(new Error('Should throw an exception'));
      });
    });
  });

  describe('convertOld', function() {
    it('should convert directly from a stream', function(done) {
      var stream = fs.createReadStream(filesPath + '/leye-old.xml',
                                       {encoding: 'utf8'});

      converter.convertOld(stream, function (err, result) {
        if (err) done (err);

        var expected = fs.readFileSync(filesPath + '/leye-old.json');

        assert.deepEqual(result, JSON.parse(expected));
        done();
      });
    });
  });

  describe('toTJS', function() {
    it('should convert a haarStruct from the new type of xml', function() {
      var fileRes = fs.readFileSync(filesPath + '/eye-tjs.json');
      var orig = fs.readFileSync(filesPath + '/eye.json');

      var expected = JSON.parse(fileRes);
      var actual = converter.toTJS(JSON.parse(orig));

      assert.deepEqual(actual, expected)
    });

    it('should convert a haarStruct from the old type of xml', function() {
      var fileRes = fs.readFileSync(filesPath + '/leye-old-tjs.json');
      var orig = fs.readFileSync(filesPath + '/leye-old.json');
      var expected = JSON.parse(fileRes);
      var actual = converter.toTJS(JSON.parse(orig));

      assert.deepEqual(actual, expected);
    });
  });
});
