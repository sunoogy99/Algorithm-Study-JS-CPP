const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let s = null;

const solution = (s) => +s;

rl.on('line', (line) => {
    s = line;
    rl.close();
}).on('close', () => {
    const res = solution(s);
    console.log(res);
    process.exit();
});