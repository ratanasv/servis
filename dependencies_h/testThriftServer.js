var thrift = require('thrift');
var http = require('http');
var querystring = require('querystring');
var url = require('url');
var assert = require('assert');
var _ = require('underscore');

var servis_types = require('./gen-nodejs/servis_types.js'),
    VISTAS = require('./gen-nodejs/VISTAS.js');

function arrays_equal(a,b) { return !(a<b || b<a); }

function testBoilerPlate(test, args, verify) {
    return function(beforeExit, assert) {
        var connection = thrift.createConnection('localhost', 9090);
        var client = thrift.createClient(VISTAS, connection);
        var done = false;
        var callbackVerify = function(err, data) {
            if (err) {
                console.error(err);
                throw err;
            } else {
                verify(assert, data);
                connection.end();
                done = true;
            }
        };

        args.push(callbackVerify);
        client[test].apply(client, args);

        beforeExit(function() {
            assert.ok(done, test + ' hasnt been executed');
        });
    };
}

exports['test_getDatasets'] = testBoilerPlate('getDatasets', [], function(assert, data) {
    assert.ok(arrays_equal(data.sort(), ['easternOregon', 'eugene', 'chesapeakeBay'].sort()));
});

exports['test_getAttributes'] = testBoilerPlate('getAttributes', ['easternOregon'], function(assert, data){
    assert.notEqual(-1, _.indexOf(data, 'LULC_A'));
    assert.notEqual(-1, _.indexOf(data, 'LULC_B'));
});

exports['test_getTerrain'] = testBoilerPlate('getTerrain', ['easternOregon'], function(assert, data) {
    assert.equal(64755*3, data.vertices.length);
    assert.equal(142563, data.indices.length);
});


