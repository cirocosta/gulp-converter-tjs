var through = require('through2');
var converter = require('./converter-tjs')();
var Readable = require('stream').Readable || require('readable-stream');

/**
 * Creates a stream w/ data.
 */
function createStream (data) {
  var rs = new Readable({ objectMode: true });
  rs.push(data);
  rs.push(null);

  return rs;
}

/**
 * The transform itself
 */
function ConverterTJS () {
  if (!(this instanceof ConverterTJS))
    return new ConverterTJS();

  function _transform (chunk, enc, callback) {
    if (!this._body) this._body = '';

    this._body += chunk.toString();

    callback();
  }

  function _flush (callback) {
    var scope = this;
    var stream = createStream(this._body);

    converter.convert(stream, function (err, data) {
      if (err) scope.emit('error', err);

      var d = JSON.stringify(converter.toTJS(data));

      scope.push(d, 'utf8');
      callback();
    });
  }

  return through.obj(_transform, _flush);
}

module.exports = ConverterTJS;
