const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let s = null;

const solution = (s) => {
    let len = s.length;
    let [first, second] = [Math.floor((len - 1) / 2), Math.ceil((len - 1) / 2)];
    if (first === second) return s[first];
    else return s[first] + s[second];
}

rl.on('line', (line) => {
    s = line;
    rl.close();
}).on('close', () => {
    const res = solution(s);
    console.log(res);
    process.exit();
});