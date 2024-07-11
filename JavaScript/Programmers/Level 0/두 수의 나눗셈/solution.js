const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let num1 = null;
let num2 = null;

// const solution = (num1, num2) => Math.floor((num1 / num2) * 1000);
const solution = (num1, num2) => Math.trunc(num1 / num2 * 1000);

rl.on('line', (line) => {
    [num1, num2] = line.split(' ').map(e => +e);
    rl.close();
}).on('close', () => {
    const res = solution(num1, num2);
    console.log(res);
    process.exit();
});