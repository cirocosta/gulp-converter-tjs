var assert = require('assert');
var converterTjs = require('../src/converter-tjs-transform');
var fs = require('fs');
var path = require('path').resolve(__dirname, './files');

describe('converterTransform', function() {
  it('be sane', function() {
    assert(!!converterTjs);
  });

  it('upperCase stuff', function(done) {
    var stream = fs.createReadStream(path + '/eye.xml');

    stream
      .pipe(converterTjs())
      .once('data', function (data) {
        var expected = fs.readFileSync(path + '/eye-tjs.json');

        assert.equal(data, expected);
        done();
      })
      .once('error', function (err) {
        done(err);
      });
  });
});
