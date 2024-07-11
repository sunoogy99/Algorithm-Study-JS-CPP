const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let s = null;

const solution = (s) => s.split('').sort((a, b) => a < b ? 1 : -1).join('');

rl.on('line', (line) => {
    s = line;
    rl.close();
}).on('close', () => {
    const res = solution(s);
    console.log(res);
    process.exit();
});