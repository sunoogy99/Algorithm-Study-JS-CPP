const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let n = null;

function converBase10ToBase3Reverse(num) {
    let res = '';

    while (num !== 0) {
        res += num % 3;
        num = Math.trunc(num / 3);
    }

    return res;
}

function convertBase3toBase10(base3) {
    return base3.split('').reverse().reduce((prev, curr, i) => prev + +curr * Math.pow(3, i), 0);
}

const solution = (n) => {
    return convertBase3toBase10(converBase10ToBase3Reverse(n));
    // return parseInt(n.toString(3).split('').reverse().join(''), 3)
}

rl.on('line', (line) => {
    n = +line;
    rl.close();
}).on('close', () => {
    const res = solution(n);
    console.log(res);
    process.exit();
});