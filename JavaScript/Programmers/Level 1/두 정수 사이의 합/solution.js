const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let a, b = [null, null];

const solution = (a, b) => {
    let [start, end] = a < b ? [a, b] : [b, a];
    let answer = 0;
    for (let i = start; i <= end; i++) {
        answer += i;
    }

    return answer;
}

rl.on('line', (line) => {
    [a, b] = line.split(' ').map(e => +e);
    rl.close();
}).on('close', () => {
    const res = solution(a, b);
    console.log(res);
    process.exit();
});