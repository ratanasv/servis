var thrift = require('thrift');

var servis_types = require('./gen-nodejs/servis_types.js'),
    VISTAS = require('./gen-nodejs/VISTAS.js');

var connection = thrift.createConnection('localhost', 9090),
    client = thrift.createClient(VISTAS, connection);

connection.on('error', function(err) {
    console.error(err);
});

console.log('entering');
client.getTerrain('foo', function(err, res) {
    console.log('entering 2');
    if (err) {
        console.error(err);
    } else {
        console.log(JSON.stringify(res));
        connection.end();
    }
});
console.log('done');
