const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let n = null;

const solution = (n) => {
    let count = 0;
    while (n != 1 && count != 500) {
        n = n % 2 ===0 ? n / 2 : n * 3 + 1;
        count++;
    }

    if (n !== 1) return -1;
    else return count;
}

rl.on('line', (line) => {
    n = +line;
    rl.close();
}).on('close', () => {
    const res = solution(n);
    console.log(res);
    process.exit();
});