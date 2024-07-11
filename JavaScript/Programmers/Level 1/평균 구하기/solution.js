const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let arr = [];

const solution = (arr) => arr.reduce((prev, curr) => prev + curr, 0) / arr.length;

rl.on('line', (line) => {
    arr = line.split(' ').map(e => +e);
    rl.close();
}).on('close', () => {
    const res = solution(arr);
    console.log(res);
    process.exit();
});