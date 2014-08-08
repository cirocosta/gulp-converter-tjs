var through = require('through2');
var converter = require('./converter');

/**
 * Creates a stream with the prefixText arg.
 */
function createStream (data) {
  var stream = through();
  stream.write(data);

  return stream;
}

function ConverterTJS () {
  if (!(this instanceof ConverterTJS))
    return new ConverterTJS();

  function _transform (chunk, enc, callback) {
    var stream = createStream(chunk.toString('utf8'));

    converter.convert(stream, function (data) {
      this.push(data, 'utf8');
      callback();
    });
  }

  return through.obj(_transform);
}

module.exports = ConverterTJS;
