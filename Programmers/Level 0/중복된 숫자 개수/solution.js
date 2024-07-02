const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let data = [];
let n = null;

const solution = (data) => data.filter(e => e === n).length;

rl.on('line', (line) => {
    if (data.length === 0) data = line.split(' ').map(e => +e);
    else {
        n = +line;
        rl.close();
    }
}).on('close', () => {
    const res = solution(data);
    console.log(res);
    process.exit();
});