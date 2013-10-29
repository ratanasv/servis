var thrift = require('thrift');
var http = require('http');
var querystring = require('querystring');
var url = require('url');
var assert = require('assert');
var _ = require('underscore');

var servis_types = require('./gen-nodejs/servis_types.js'),
    VISTAS = require('./gen-nodejs/VISTAS.js');

function arrays_equal(a,b) { return !(a<b || b<a); }

exports['test_getDatasets'] = function(beforeExit, assert) {
    var connection = thrift.createConnection('localhost', 9090);
    var client = thrift.createClient(VISTAS, connection);
    client.getDatasets(function(err, data) {
        if (err) {
            console.error(err);
            throw err;
        } else {
            assert.ok(arrays_equal([1,2,3], [1,2,3]));
            assert.ok(arrays_equal(data.sort(), ['easternOregon', 'chesapeakeBay', 'eugene'].sort()));
            connection.end();

        }
    });

}

exports['test_getAttributes'] = function(beforeExit, assert) {
    var connection = thrift.createConnection('localhost', 9090);
    var client = thrift.createClient(VISTAS, connection);
    client.getAttributes('eastern_oregon', function(err, data) {
        if (err) {
            console.error(err);
            throw err;
        } else {
            assert.notEqual(-1, _.indexOf(data, 'LULC_A'));
            connection.end();

        }
    });

}
