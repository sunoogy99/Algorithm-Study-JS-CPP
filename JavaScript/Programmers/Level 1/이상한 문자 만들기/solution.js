const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let s = null;

const solution = (s) => {
    return s.split(' ').map(word => {
        return word
        .split('')
        .map((e, i) => e = (i % 2 === 0) ? e.toUpperCase() : e.toLowerCase())
        .join('');
    }).join(' ');
}

rl.on('line', (line) => {
    s = line;
    rl.close();
}).on('close', () => {
    const res = solution(s);
    console.log(res);
    process.exit();
});