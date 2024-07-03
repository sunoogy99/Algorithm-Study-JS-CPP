const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let phone_number = null;

const solution = (phone_number) => {
    return phone_number.split('').map((e, i) => e = i < phone_number.length - 4 ? '*' : e).join('');
}

rl.on('line', (line) => {
    phone_number = line;
    rl.close();
}).on('close', () => {
    const res = solution(phone_number);
    console.log(res);
    process.exit();
});