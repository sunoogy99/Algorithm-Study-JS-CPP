const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let d = null;
let budget = null;

const solution = (d, budget) => {
    let sum = 0;
    // 많이 지원해주려면 오름차순으로 정렬하고
    // 맨 처음부터 지원 가능한 예산까지 인덱스 선택
    return d.sort((a, b) => a - b).map(e => {
        sum += e;
        return sum;
    }).filter(e => e <= budget).length;
}

rl.on('line', (line) => {
    if (!d) {
        d = line.split(' ').map(e => +e);
    }
    else {
        budget = +line;
    }

    if (d && budget) {
        rl.close();
    }
}).on('close', () => {
    const res = solution(d, budget);
    console.log(res);
    process.exit();
});