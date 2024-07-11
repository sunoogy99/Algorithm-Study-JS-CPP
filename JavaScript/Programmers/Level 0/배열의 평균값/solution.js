const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let numbers = [];

const solution = (numbers) => {
    return numbers.reduce((prev, curr) => prev + curr, 0) / numbers.length;
}

rl.on('line', (line) => {
    numbers = line.split(' ').map(e => +e);
    rl.close();
}).on('close', () => {
    const res = solution(numbers);
    console.log(res);
    process.exit();
});