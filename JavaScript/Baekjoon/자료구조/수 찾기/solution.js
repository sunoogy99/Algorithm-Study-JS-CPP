const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let N = null;
let M = null;
let number = [];
let findNumber = [];

const solution = (number, findNumber) => {
    const numDict = {};
    for (let num of number) {
        numDict[num] = 1;
    }

    const ans = [];
    for (let num of findNumber) {
        if (numDict[num] === undefined) {
            ans.push(0);
        } else {
            ans.push(1);
        }
    }

    return ans.join('\n');
}

rl.on('line', (line) => {
    if (!N) {
        N = +line;
    } else if (number.length === 0) {
        number = line.split(' ').map(e => +e);
    } else if (!M) {
        M = +line;
    } else {
        findNumber = line.split(' ').map(e => +e);
    }

    if (N && number.length !== 0 && M && findNumber.length !== 0) {
        rl.close();
    }
}).on('close', () => {
    const res = solution(number, findNumber);
    console.log(res);
    process.exit();
});