const solution = (a, b) => {
    return a - b;
}

module.exports = solution;

const readline = require('readline');

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
});

let data = [];

rl.on('line', (line) => {
    data = line.split(' ').map(e => +e);
    rl.close();
});

rl.on('close', () => {
    console.log(solution(data[0], data[1]));
    process.exit();
});