const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let money = null;

const solution = (money) => [Math.trunc(money / 5500), money % 5500];

rl.on('line', (line) => {
    money = +line;
    rl.close();
}).on('close', () => {
    const res = solution(money);
    console.log(res);
    process.exit();
});