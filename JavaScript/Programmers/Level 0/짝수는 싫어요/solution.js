const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let n = null;

const solution = (n) => Array.from(Array(n), (e, i) => i + 1).filter(e => e % 2 === 1);

rl.on('line', (line) => {
    n = +line;
    rl.close();
}).on('close', () => {
    const res = solution(n);
    console.log(res);
    process.exit();
});