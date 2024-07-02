const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let absolutes = [];
let signs = [];

const solution = (absolutes, signs) => {
    return absolutes.reduce((prev, curr, idx) => prev + curr * (signs[idx] ? 1 : -1), 0);
}

rl.on('line', (line) => {
    if (absolutes.length === 0) {
        absolutes = line.split(' ').map(e => +e);
    } else if (signs.length === 0) {
        signs = line.split(' ').map(e => e === 'true' ? true : false);
    } 

    if (absolutes.length !== 0 && signs .length !== 0) {
        rl.close();
    }
}).on('close', () => {
    const res = solution(absolutes, signs);
    console.log(res);
    process.exit();
});