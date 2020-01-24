const ascii85 = require('..');
const worker = require('worker_threads');


console.log('Encode test:');
const src = Buffer.from('Hello world!')
const result = ascii85.stringify(src);
console.log('Encode result:', src, '->', result);

console.log('Decode test:');
const result2 = ascii85.parse(result);
console.log('Decoding result:', result, '->', result2);

console.log('Context-awareness test:');
if (worker.isMainThread) {
    const wk = new worker.Worker(__filename);
} else {
    console.log('Worker passed the test.');
}
