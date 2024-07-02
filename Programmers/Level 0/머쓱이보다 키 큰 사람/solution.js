const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let array = [];
let height = null;

const solution = (array, height) => array.filter(e => e > height).length;

rl.on('line', (line) => {
    if (array.length === 0) array = line.split(' ').map(e => +e);
    else {
        height = +line;
        rl.close();
    }
}).on('close', () => {
    const res = solution(array, height);
    console.log(res);
    process.exit();
});