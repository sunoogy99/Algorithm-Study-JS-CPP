const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let s = null;

const solution = (s) => {
    if ((s.length === 4 || s.length === 6) && s.search(/[a-z]/i) === -1) return true;
    else return false;
}

rl.on('line', (line) => {
    s = line;
    rl.close();
}).on('close', () => {
    const res = solution(s);
    console.log(res);
    process.exit();
});