const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let n = null;

const solution = (n) => {
    const pattern = ['수', '박'];
    return Array.from(Array(n), (_, i) => pattern[i % 2]).join('');
    // 문자열.repeat(횟수) 이용한 방법도 있음
}

rl.on('line', (line) => {
    n = +line;
    rl.close();
}).on('close', () => {
    const res = solution(n);
    console.log(res);
    process.exit();
});