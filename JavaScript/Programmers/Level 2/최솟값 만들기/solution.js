const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let A = null;
let B = null;

// 하나는 최솟값 정렬, 하나는 최댓값 정렬해서 서로 곱해준 것이 최소가 된다고 생각했음
const solution = (A, B) => {
    A.sort((a, b) => a - b);
    B.sort((a, b) => b - a);

    return A.reduce((prev, curr, i) => prev + curr * B[i], 0);
}

rl.on('line', (line) => {
    if (!A) {
        A = line.split(' ').map(e => +e);
    } else if (!B) {
        B = line.split(' ').map(e => +e);
    }

    if (A && B) {
        rl.close();
    }
}).on('close', () => {
    const res = solution(A, B);
    console.log(res);
    process.exit();
});