const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let N = null;
let withdrawlTime = [];

// 오름차순으로 정렬 (그리디)
// 누적합 배열을 만들고 합 구하기
const solution = (withdrawlTime) => {
    let cumSum = 0;
    return withdrawlTime
    .sort((a, b) => a - b)
    .map(e => {
        cumSum += e;
        return cumSum;
    })
    .reduce((prev, curr) => prev + curr, 0);
}

rl.on('line', (line) => {
    if (!N) {
        N = +line;
    } else {
        withdrawlTime = line.split(' ').map(e => +e);
    }

    if (N && withdrawlTime.length !== 0) {
        rl.close();
    }
}).on('close', () => {
    const res = solution(withdrawlTime);
    console.log(res);
    process.exit();
});