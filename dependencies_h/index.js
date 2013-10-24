var thrift = require('thrift');
var http = require('http');
var querystring = require('querystring');
var url = require('url');


var servis_types = require('./gen-nodejs/servis_types.js'),
    VISTAS = require('./gen-nodejs/VISTAS.js');

function jsonpHandler(req, res) {
    var connection = thrift.createConnection('localhost', 9090),
        client = thrift.createClient(VISTAS, connection);
    var queryString = querystring.parse(url.parse(req.url).query);

    connection.on('error', function(err) {
        console.error(err);
    });

    client.getTerrain(queryString.fileName, function(err, data) {
        var payload;

        if (err) {
            console.error(err);
        } else {
            res.writeHead(200, {"Content-Type": "application/javascript"});
            payload = queryString.callback + '(' + JSON.stringify(data) + ');';
            res.write(payload);
            connection.end();
            res.end();
        }
    });
}

http.createServer(jsonpHandler).listen(8888);


