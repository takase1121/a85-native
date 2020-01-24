const ascii85 = require('..');
const worker = require('worker_threads');

const assert = require('assert').strict;

if (worker.isMainThread) {
    process.stdout.write('Encode test: ');
    const src = Buffer.from('Hello world!')
    const result = ascii85.stringify(src);
    assert.equal(result, '87cURD]j7BEbo80', 'Assertion failed for encoding test');
    console.log('OK');

    process.stdout.write('Decode test: ');
    const result2 = ascii85.parse(result);
    assert.ok(src.equals(result2), 'Assertion failed for decoding test');
    console.log('OK');

    process.stdout.write('Context-awareness test: ');
    const wk = new worker.Worker(__filename);
    wk.ref();
    wk.once('message', () => console.log('OK'));
    wk.once('error', () => console.log('FAIL'));
} else {
    worker.parentPort.postMessage(true);
}