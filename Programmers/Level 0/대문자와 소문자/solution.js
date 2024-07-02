const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let my_string = null;

const solution = (my_string) => {
    return my_string.split('').map(e => {
        if (e === e.toUpperCase()) return e.toLowerCase();
        else return e.toUpperCase();
    }).join('');
}

rl.on('line', (line) => {
    my_string = line;
    rl.close();
}).on('close', () => {
    const res = solution(my_string);
    console.log(res);
    process.exit();
});