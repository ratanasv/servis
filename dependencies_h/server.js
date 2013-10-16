var thrift = require('thrift');

var VISTAS = require('./gen-nodejs/VISTAS.js'),
    servis_types = require('./gen-nodejs/servis_types.js');



var server = thrift.createServer(VISTAS, {
    getTerrain: function(fileName, result) {
        console.log('getTerrain:' + fileName);
        result(null, 1);
    }
});

server.listen(9090);
