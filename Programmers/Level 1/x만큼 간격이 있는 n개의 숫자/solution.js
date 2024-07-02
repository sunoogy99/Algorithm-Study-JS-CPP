const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let x = null;
let n = null;

const solution = (x, n) => Array.from(Array(n), (e, i) => x * (i + 1));

rl.on('line', (line) => {
    [x, n] = line.split(' ').map(e => +e);
    rl.close();
}).on('close', () => {
    const res = solution(x, n);
    console.log(res);
    process.exit();
});