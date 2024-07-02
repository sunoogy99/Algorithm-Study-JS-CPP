const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let numbers = [];

const solution = (numbers) => {
    let checkArray = Array(10).fill(false);
    numbers.map(e => checkArray[e] = true);
    return checkArray.reduce((prev, curr, idx) => prev + (curr ? 0 : idx), 0);
    // return 45 - numbers.reduce((prev, curr) => prev + curr, 0);
}

rl.on('line', (line) => {
    numbers = line.split(' ').map(e => +e);
    rl.close();
}).on('close', () => {
    const res = solution(numbers);
    console.log(res);
    process.exit();
});