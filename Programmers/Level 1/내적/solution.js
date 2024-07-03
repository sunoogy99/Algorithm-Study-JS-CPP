const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let a = null;
let b = null;

const solution = (a, b) => a.reduce((prev, curr, idx) => prev + a[idx] * b[idx], 0);

rl.on('line', (line) => {
    if (!a) {
        a = line.split(' ').map(e => +e);
    }
    else if (!b) {
        b = line.split(' ').map(e => +e);
    }
    
    if (a && b) {
        rl.close();
    }
}).on('close', () => {
    const res = solution(a, b);
    console.log(res);
    process.exit();
});