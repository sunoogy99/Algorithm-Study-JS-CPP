const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let age = null;

function solution(age) {
    const currentYear = 2022;
    return currentYear - age + 1;
}

rl.on('line', (line) => {
    age = +line;
    rl.close();
}).on('close', () => {
    let res = solution(age);
    console.log(res);
    process.exit();
});