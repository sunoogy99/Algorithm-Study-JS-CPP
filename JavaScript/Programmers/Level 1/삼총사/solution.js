const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let number = null;

// 너무 싫지만 입력 범위가 13까지라 3중 for문 충분히 돌아감
const solution = (number) => {
    let len = number.length;
    let ans = 0;
    for (let i = 0; i < len - 2; i++) {
        for (let j = i + 1; j < len - 1; j++) {
            for (let k = j + 1; k < len; k++) {
                if (number[i] + number[j] + number[k] === 0) ans++;
            }
        }
    }

    return ans;
}

rl.on('line', (line) => {
    number = line.split(' ').map(e => +e);
    rl.close();
}).on('close', () => {
    const res = solution(number);
    console.log(res);
    process.exit();
});