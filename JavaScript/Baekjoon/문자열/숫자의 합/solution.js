const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let N = null;
let numbers = [];

const solution = (numbers) => numbers.reduce((prev, curr) => prev + curr, 0);

rl.on('line', (line) => {
    if (!N) {
        N = +line;
    } else {
        numbers = line.split('').map(e => +e);
    }

    if (N && numbers.length !== 0) {
        rl.close();
    }
}).on('close', () => {
    const res = solution(numbers);
    console.log(res);
    process.exit();
});