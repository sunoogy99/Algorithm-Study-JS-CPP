const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let cipher = null;
let code = null;

const solution = (cipher, code) => cipher.split('').filter((e, i) => (i + 1) % code === 0).join('');

rl.on('line', (line) => {
    [cipher, code] = line.split(' ');
    code = +code;
    rl.close();
}).on('close', () => {
    const res = solution(cipher, code);
    console.log(res);
    process.exit();
});