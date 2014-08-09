var through = require('through2');
var converter = require('./converter-tjs')();
var Readable = require('stream').Readable || require('readable-stream');
var PluginError = require('gulp-util').PluginError;
var PLUGIN_NAME = 'gulp-converter-tjs';

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
    if (file.isStream()) {
      this.emit('error', new PluginError(PLUGIN_NAME, 'Streams are not supported!'));
      return callback();
    }

    this.file = file;

    if (!this._body)
      this._body = '';
    this._body += file.contents.toString();

    callback();
  }

  function _flush (callback) {
    var scope = this;
    var stream = createStream(this._body);

    stream.on('error', this.emit.bind(this, 'error'));
    converter.convert(stream, function (err, data) {
      if (err)
        return (scope.emit('error', new PluginError(PLUGIN_NAME, err)),
                callback());

      scope.file.contents = new Buffer(JSON.stringify(converter.toTJS(data)));
      scope.push(scope.file);
      callback();
    });
  }

  return through.obj(_transform, _flush);
}

module.exports = ConverterTJS;
