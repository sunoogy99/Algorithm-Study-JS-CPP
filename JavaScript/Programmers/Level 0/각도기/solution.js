const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let angle = null;

const solution = (angle) => {
    if (angle > 0 && angle < 90) return 1;
    else if (angle === 90) return 2;
    else if (angle > 90 && angle < 180) return 3;
    else if (angle === 180) return 4;
    else return -1;
}

rl.on('line', (line) => {
    angle = +line;
    rl.close();
}).on('close', () => {
    const res = solution(angle);
    console.log(res);
    process.exit();
});