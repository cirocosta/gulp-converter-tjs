var fs = require('fs')
	,	path = require('path')
	,	XmlStream = require('xml-stream')
	,	filename = path.resolve(__dirname, '../files/eye.xml');
	,	stream = fs.createReadStream(filename)
	,	xml = new XmlStream(stream)
	,	count = 0;

xml.collect('_');

xml.on('endElement: weakClassifiers > _', function(item) {
	count++;
  console.log(item);
});

xml.on('endElement: features > _ > rects', function(item) {
	count++;
  console.log('--- ',item);
});


xml.on('end', function () {
	console.log('\nfinished! ' + count);
})

