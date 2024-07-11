const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let N = null;
let M = null;
let cards = [];

const solution = (N, M, cards) => {
    let ans = 0;

    // 100C3 => 1초 안에 수행 가능 : 완전 탐색
    for (let i = 0; i < N - 2; i++) {
        for (let j = i + 1; j < N - 1; j++) {
            for (let k = j + 1; k < N; k++) {
                let sum = cards[i] + cards[j] + cards[k];
                ans = sum <= M ? Math.max(ans, sum) : ans;
            }
        }
    }

    return ans;
}

rl.on('line', (line) => {
    if (!N && !M) {
        [N, M] = line.split(' ').map(e => +e);
    } else {
        cards = line.split(' ').map(e => +e);
    }

    if (N && M && cards.length !== 0) {
        rl.close();
    }
}).on('close', () => {
    const res = solution(N, M, cards);
    console.log(res);
    process.exit();
});