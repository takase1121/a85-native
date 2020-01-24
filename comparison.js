const ascii85 = require('.');
const { join } = require('path');
const { readFileSync } = require('fs');

const file = readFileSync(join(__dirname, 'test', 'blah.bin'));

const b64 = file.toString('base64').length;
const a85 = ascii85.stringify(file).length;
console.log('Base64: %d -> %d (%d%%)', file.length, b64, (b64/file.length*100) - 100);
console.log('ascii85: %d -> %d (%d%%)', file.length, a85, (a85/file.length*100) - 100);

