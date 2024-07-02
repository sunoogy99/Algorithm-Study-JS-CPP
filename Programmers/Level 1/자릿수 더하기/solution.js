const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let N = null;

const solution = (N) => N.toString().split('').reduce((prev, curr) => prev + +curr, 0);

rl.on('line', (line) => {
    N = +line;
    rl.close();
}).on('close', () => {
    const res = solution(N);
    console.log(res);
    process.exit();
});