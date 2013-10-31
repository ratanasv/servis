var thrift = require('thrift');
var http = require('http');
var querystring = require('querystring');
var url = require('url');
var winston = require('winston');
var colors = require('colors');

var servis_types = require('./gen-nodejs/servis_types.js'),
    VISTAS = require('./gen-nodejs/VISTAS.js');

winston.add(winston.transports.File, {
    filename: 'servis.log',
    timestamp: function() {
        return new Date().toLocaleString();
    },
    colorize: false
});
winston.remove(winston.transports.Console);
winston.add(winston.transports.Console, {
    timestamp: function() {
        return new Date().toLocaleDateString() + ' ' + new Date().toLocaleTimeString();
    },
    colorize: true
});
winston.addColors({
    info: 'blue',
    warn: 'yellow',
    error: 'red'
});

function getOnThriftCallBack(response, connection, queryString) {
    return function(err, data) {
        var payload;
        if (err) {
            winston.error(err);
            response.writeHead(500, {"Content-Type": "application/javascript"});
        } else {
            response.writeHead(200, {"Content-Type": "application/javascript"});
            payload = queryString.callback + '(' + JSON.stringify(data) + ');';
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
        winston.error(err);
        res.writeHead(503, {"Content-Type": "application/javascript"});
        res.end();
    });
    onThriftCallBack = getOnThriftCallBack(res, connection, queryString);
    winston.info(JSON.stringify({
        ip: req.connection.remoteAddress,
        queryString: queryString
    }));

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
        winston.warn('method:' + queryString.method + ' not supported');
        res.writeHead(503, {"Content-Type": "application/javascript"});
        res.end();
        connection.end();
        break;
    }
}

http.createServer(jsonpHandler).listen(8888);


