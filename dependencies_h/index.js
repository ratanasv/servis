var thrift = require('thrift');
var http = require('http');
var querystring = require('querystring');
var url = require('url');


var servis_types = require('./gen-nodejs/servis_types.js'),
    VISTAS = require('./gen-nodejs/VISTAS.js');

function getOnThriftCallBack(response, connection) {
    return function(err, data) {
        var payload;
        if (err) {
            console.error(err);
            response.writeHead(500, {"Content-Type": "application/javascript"});
        } else {
            response.writeHead(200, {"Content-Type": "application/javascript"});
            payload = querystring.callback + '(' + JSON.stringify(data) + ');';
            response.write(payload);
        }
        connection.end();
        response.end();
    }
}

function jsonpHandler(req, res) {
    var connection = thrift.createConnection('localhost', 9090),
        client = thrift.createClient(VISTAS, connection);
    var queryString = querystring.parse(url.parse(req.url).query);
    var onThriftCallBack;

    connection.on('error', function(err) {
        console.error(err);
        res.writeHead(503, {"Content-Type": "application/javascript"});
        res.end();
    });
    onThriftCallBack = getOnThriftCallBack(res, connection);
    console.log('ip=' + req.connection.remoteAddress + ' queryString=' + JSON.stringify(queryString));

    switch(queryString.method) {
    case 'getTerrain':
        client.getTerrain(queryString.fileName, onThriftCallBack);
        break;
    case 'getColor':
        client.getColor(queryString.fileName, queryString.attribute, onThriftCallBack);
        break;
    case 'getNormalMap':
        client.getNormalMap(queryString.fileName, onThriftCallBack);
        break;
    case 'getTextureMap':
        client.getTextureMap(queryString.fileName, onThriftCallBack);
        break;
    case 'getAttributes':
        client.getAttributes(queryString.fileName, onThriftCallBack);
        break;
    case 'getDatasets':
        client.getDatasets(onThriftCallBack);
        break;
    default:
        throw 'method not supported:' + queryString.method;
        break;
    }
}

http.createServer(jsonpHandler).listen(8888);


