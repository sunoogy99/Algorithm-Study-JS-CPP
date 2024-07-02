const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let seoul = [];

const solution = (seoul) => {
    const kimIdx = seoul.findIndex(e => e === 'Kim');
    return `김서방은 ${kimIdx}에 있다`;
}

rl.on('line', (line) => {
    seoul = line.split(' ');
    rl.close();
}).on('close', () => {
    const res = solution(seoul);
    console.log(res);
    process.exit();
});