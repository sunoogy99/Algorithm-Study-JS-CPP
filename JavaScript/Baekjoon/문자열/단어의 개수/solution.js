const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let str = null;

const solution = (str) => str.split(' ').filter(e => e !== '').length;

rl.on('line', (line) => {
    str = line;
    rl.close();
}).on('close', () => {
    const res = solution(str);
    console.log(res);
    process.exit();
});