const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let n = null;

const solution = (n) => {
    const rootN = Math.pow(n, 0.5);
    return rootN > Math.trunc(rootN) ? -1 : Math.pow(rootN + 1, 2);
}

rl.on('line', (line) => {
    n = +line;
    rl.close();
}).on('close', () => {
    const res = solution(n);
    console.log(res);
    process.exit();
});