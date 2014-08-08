var gulp = require('gulp');
var converterTjs = require('./src/gulp-converter-tjs');

gulp.task('default', function () {
  gulp.src('./files/xml.xml', {buffer: true})
    .pipe(converterTjs())
    .pipe(gulp.dest('./modified-files'));
});
