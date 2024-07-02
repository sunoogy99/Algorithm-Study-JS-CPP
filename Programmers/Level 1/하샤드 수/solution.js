const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let x = null;

const solution = (x) => {
    let pSum = (x + "").split('').reduce((prev, curr) => prev + +curr, 0);
    return x % pSum === 0;
}

rl.on('line', (line) => {
    x = +line;
    rl.close();
}).on('close', () => {
    const res = solution(x);
    console.log(res);
    process.exit();
});