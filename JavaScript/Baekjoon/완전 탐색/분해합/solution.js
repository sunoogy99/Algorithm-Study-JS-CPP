const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let N = null;

const solution = (N) => {
    let minConstructor = 0; // 생성자가 없는 경우 0을 반환한다.

    // 가장 작은 생성자를 찾는 것이므로, 생성자를 찾으면 바로 반환한다.
    for (let i = 1; i <= N; i++) {
        let disassembleSum = (i + "").split('').map(e => +e).reduce((prev, curr) => prev + curr, i);
        if (disassembleSum === N) {
            minConstructor = i;
            break;
        }
    }

    return minConstructor;
}

rl.on('line', (line) => {
    N = +line;
    rl.close();
}).on('close', () => {
    const res = solution(N);
    console.log(res);
    process.exit();
});