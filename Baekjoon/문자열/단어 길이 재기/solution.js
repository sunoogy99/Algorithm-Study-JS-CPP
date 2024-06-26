const solution = (input) => {
    return input.length;
}

module.exports = solution;

const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let data = '';

rl.on('line', (line) => {
    data = line;
    rl.close();
}).on('close', () => {
    console.log(solution(data));
    process.exit();
});