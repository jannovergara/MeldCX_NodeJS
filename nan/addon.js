var addon = require('bindings')('addon.node')

console.log('Monitor information: ', addon.GetMonitorInfo())