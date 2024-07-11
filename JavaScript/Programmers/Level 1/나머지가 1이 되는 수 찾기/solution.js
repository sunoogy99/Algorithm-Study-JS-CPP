const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let n = null;

const solution = (n) => {
    // 가장 작은 자연수 x를 구하는 것이므로
    // 반복문에서 나머지 1이 되는 수를 찾으면 바로 반환하기
    for (let i = 2; i < n; i++) {
        if (n % i === 1) return i;
    }

    return 'No Answer';
}

rl.on('line', (line) => {
    n = +line;
    rl.close();
}).on('close', () => {
    const res = solution(n);
    console.log(res);
    process.exit();
});