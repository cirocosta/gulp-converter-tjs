'use strict';

var through = require('through2')
  , converter = require('./converter-tjs')()
  , Readable = require('stream').Readable || require('readable-stream')
  , PluginError = require('gulp-util').PluginError
  , NAME = 'gulp-converter-tjs';

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

  function _transform (file, enc, callback) {
    if (file.isStream())
      return (this.emit('error', new PluginError(NAME, 'Streams are not supported!')),
              callback());

    this.file = file;

    if (file.isBuffer()) {
      if (!this._body)
        this._body = '';
      this._body += file.contents.toString();

      callback();
    }
  }

  function _flush (callback) {
    var scope = this;
    var stream = createStream(this._body);

    stream.on('error', this.emit.bind(this, 'error'));
    converter.convert(stream, function (err, data) {
      if (err)
        return (scope.emit('error', new PluginError(NAME, err)),
                callback());

      scope.file.contents = new Buffer(JSON.stringify(converter.toTJS(data)));
      scope.push(scope.file);
      callback();
    });
  }

  return through.obj(_transform, _flush);
}

module.exports = ConverterTJS;
