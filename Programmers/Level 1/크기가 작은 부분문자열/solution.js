const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let t = null;
let p = null;

const solution = (t, p) => {
    let start = 0;
    let end = p.length;
    let count = 0;

    while (end !== t.length + 1) {
        console.log(parseInt(t.substring(start, end)), +p);
        if (parseInt(t.substring(start, end)) <= +p) {
            count++;
        }

        start++;
        end++;
    }

    return count;
}

rl.on('line', (line) => {
    [t, p] = line.split(' ');
    rl.close();
}).on('close', () => {
    const res = solution(t, p);
    console.log(res);
    process.exit();
});