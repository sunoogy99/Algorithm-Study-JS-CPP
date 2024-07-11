const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let array = [];

const solution = (array) => array.sort((a, b) => a - b)[Math.floor((array.length - 1) / 2)];

rl.on('line', (line) => {
    array = line.split(' ').map(e => +e);
    rl.close();
}).on('close', () => {
    const res = solution(array);
    console.log(res);
    process.exit();
});