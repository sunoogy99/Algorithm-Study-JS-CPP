const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let num = null;

const solution = (num) => num % 2 === 0 ? "Even" : "Odd";

rl.on('line', (line) => {
    num = +line;
    rl.close();
}).on('close', () => {
    const res = solution(res);
    console.log(res);
    process.exit();
});