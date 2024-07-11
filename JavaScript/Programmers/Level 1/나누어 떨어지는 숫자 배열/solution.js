const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let arr = [];
let divisor = null;

const solution = (arr, divisor) => {
    let ans = arr.filter(e => e % divisor === 0);
    return ans.length > 0 ? ans.sort((a, b) => a - b) : [-1];
}

rl.on('line', (line) => {
    if (arr.length === 0) {
        arr = line.split(' ').map(e => +e);
    } else {
        divisor = +line;
    }

    if (divisor !== null && arr.length !== 0) {
        rl.close();
    }
}).on('close', () => {
    const res = solution(arr, divisor);
    console.log(res);
    process.exit();
});