const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let n = null;

const solution = (n) => parseInt((n + "").split('').sort((a, b) => b - a).join(''));

rl.on('line', (line) => {
    n = +line;
    rl.close();
}).on('close', () => {
    const res = solution(n);
    console.log(res);
    process.exit();
});