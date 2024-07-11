const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let n = null;

/// Array.from(배열, 매핑함수)
const solution = (n) => Array.from(Array(n), (e, i) => i + 1).filter(e => e % 2 === 0).reduce((prev, curr) => prev + curr, 0);

rl.on('line', (line) => {
    n = +line;
    rl.close();
}).on('close', () => {
    const res = solution(n);
    console.log(res);
    process.exit();
});