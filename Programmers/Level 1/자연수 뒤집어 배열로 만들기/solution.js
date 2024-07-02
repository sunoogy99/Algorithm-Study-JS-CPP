const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let n = null;

// reverse() : inplace, O(N)
// reversed() : view 반환, O(1)
const solution = (n) => n.toString().split('').reverse().map(e => +e);

rl.on('line', (line) => {
    n = +line;
    rl.close();
}).on('close', () => {
    const res = solution(n);
    console.log(res);
    process.exit();
});