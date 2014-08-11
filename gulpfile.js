/**
 * Example of a gulpfile
 */

var gulp = require('gulp');
var converterTjs = require('./src/converter-tjs-transform');

gulp.task('default', function () {
  gulp.src('./test/files/haarcascade_frontalface_alt.xml')
    .pipe(converterTjs())
    .pipe(gulp.dest('./modified-files'));
});
