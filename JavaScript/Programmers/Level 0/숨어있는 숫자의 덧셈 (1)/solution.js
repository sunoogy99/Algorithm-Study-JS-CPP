const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let my_string = null;

const solution = (my_string) => my_string.split('').filter(e => +e > 0).map(e => +e).reduce((prev, curr) => prev + curr, 0);

rl.on('line', (line) => {
    my_string = line;
    rl.close();
}).on('close', () => {
    const res = solution(my_string);
    console.log(res);
    process.exit();
});