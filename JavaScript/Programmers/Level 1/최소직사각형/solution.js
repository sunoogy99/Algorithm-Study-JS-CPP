const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let n = null;
let sizes = [];
let count = 0;

const solution = (sizes) => {
    sizes.map(e => {
        if (e[0] < e[1]) {
            // 얕은 복사 -> 실제 데이터 변경
            [e[0], e[1]] = [e[1], e[0]];
        }

        return e;
    });

    let leftMax = Math.max(...sizes.map(e => e[0]));
    let rightMax = Math.max(...sizes.map(e => e[1]));
    return leftMax * rightMax;
}

rl.on('line', (line) => {
    if (!n) {
        n = +line;
    }
    else {
        sizes.push(line.split(' ').map(e => +e));
        count++;
    }

    if (count === n) {
        rl.close();
    }
}).on('close', () => {
    const res = solution(sizes);
    console.log(res);
    process.exit();
});