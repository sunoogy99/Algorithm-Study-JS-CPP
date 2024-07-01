const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let num1 = null;
let num2 = null;

const solution = (num1, num2) => num1 * num2;

rl.on('line', (line) => {
    [num1, num2] = line.split(' ').map(e => +e);
    rl.close();
}).on('close', () => {
    let res = solution(num1, num2);
    console.log(res);
    process.exit();
});