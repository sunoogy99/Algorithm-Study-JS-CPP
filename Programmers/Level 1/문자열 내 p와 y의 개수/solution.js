const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let s = null;

const solution = (s) => {
    let pCount = 0;
    let yCount = 0;

    s.split('').map(e => {
        switch (e.toLowerCase()) {
            case 'p':
                pCount++;
                break;
            case 'y':
                yCount++;
                break;
            default:
                break;
        } 
    });

    return pCount === yCount;
    // return s.toLowerCase().split('p').length === s.toLowerCase().split('y').length;
}

rl.on('line', (line) => {
    s = line;
    rl.close();
}).on('close', () => {
    const res = solution(s);
    console.log(res);
    process.exit();
});